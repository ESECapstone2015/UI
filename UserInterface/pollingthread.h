#ifndef POLLINGTHREAD_H
#define POLLINGTHREAD_H

#include <QThread>
#include "Serial.h"


class PollingThread : public QThread {
    void run();
signals:
    void updatePosition(qint64 posx, qint64 posy);

};

void PollingThread::run(){
    // Open Serial port
    Serial * serialThread = new Serial();
    HANDLE serialPort = serialThread->openSerial();
    // Update position data.
    while (1){
        serialThread->getData(serialPort);
        emit updatePosition(serialThread->getx(), serialThread->gety());
    }
}

void PollingThread::updatePosition(qint64 posx, qint64 posy){
    //
}

#endif // POLLINGTHREAD_H

