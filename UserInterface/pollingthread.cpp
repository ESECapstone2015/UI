#include "pollingthread.h"

void PollingThread::pollPort(){
    // Open Serial port
    Serial * serialThread = new Serial();
    HANDLE serialPort = serialThread->openSerial();

    int i = 0;

    if (serialPort != NULL){
        emit sendDebug("Serial Port opened successfully.");
    }
    else {
        emit sendDebug("Serial Port not opened, ERROR.");
    }

    // Update position data.
    while (1){
        serialThread->getData(serialPort);
        if (i == 1000 ){
            emit updatePosition(serialThread->getx(), serialThread->gety());
        }
        i++;
    }
}
