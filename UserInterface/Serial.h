#ifndef SERIAL_H
#define SERIAL_H

//** Written by Mark Mahony & Nick Oudyk
//** Wrapper code borrowed from 
//** http://www.codeproject.com/Articles/9903/Calling-Managed-Code-from-Unmanaged-Code-and-vice
#include <stdio.h>
#include <Windows.h>
#include <QString>
#include <QStringList>
#include <QDebug>

#define COMPORT "COM10"
#define PANRATE 1
#define CNTR_INIT 500
#define WINXSIZE 500
#define WINYSIZE 500

class Serial
{
private:
	double xangle = 0, yangle = 0, zangle = 0;
	int windowX = CNTR_INIT, windowY = CNTR_INIT;
	int winxsize = WINXSIZE;
	int winysize = WINYSIZE;
        void parseBuffer(char * buffer);
	void updateWindow();


public:
    Serial(){}
    ~Serial(){}
	int getData(HANDLE port);
	HANDLE openSerial();
	int getx();
	int gety();
};


#endif
