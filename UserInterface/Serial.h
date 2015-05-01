//** Written by Mark Mahony & Nick Oudyk
//** Wrapper code borrowed from 
//** http://www.codeproject.com/Articles/9903/Calling-Managed-Code-from-Unmanaged-Code-and-vice
#include <stdio.h>
#include <Windows.h>
#using <System.dll>

#ifndef WINUP_H
#define WINUP_H
#define COMPORT "COM10"
#define PANRATE 1
#define CNTR_INIT 500
#define WINXSIZE 1000
#define WINYSIZE 1000

public class WindowUpdate
{
private:
	double xangle = 0, yangle = 0, zangle = 0;
	int windowX = CNTR_INIT, windowY = CNTR_INIT;
	int winxsize = WINXSIZE;
	int winysize = WINYSIZE;
	void parseBuffer(char * buffer, int length);
	void updateWindow();


public:
	WindowUpdate(){}
	~WindowUpdate(){}
	int getData(HANDLE port);
	HANDLE openSerial();
	int getx();
	int gety();
};


#endif