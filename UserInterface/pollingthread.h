#ifndef POLLINGTHREAD_H
#define POLLINGTHREAD_H

#include <QThread>
#include <QTimer>
#include <QTextStream>
#include <iostream>
#include "Serial.h"


class PollingThread : public QObject {
    Q_OBJECT
signals:
    void updatePosition(qint64 posx, qint64 posy);
    void sendDebug(QString msg);
public slots:
    void pollPort();
};

#endif // POLLINGTHREAD_H

