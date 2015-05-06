// Some code borrowed from http://stackoverflow.com/questions/14545961/modify-qt-gui-from-background-worker-thread
// Written by Mark Mahony, May 1st, 2015
// Polls serial port for new position data, then updates dot on screen based on data.

#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pollingthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onUpdatePosition(qint64 posx, qint64 posy){
    QMessageBox msgBox;
    msgBox.setText("Position X:" + QString::number(posx)  + "Position Y:" + QString::number(posy));
    ui->dot->setGeometry(posx,posy,16,16);
}

void MainWindow::StartPolling(){
    //Create worker thread.
    PollingThread *workerThread = new PollingThread;
    //Connect slots and signals to update dot position.
    connect(workerThread, SIGNAL(PollingThread::updatePosition(qint64,qint64)),SLOT(onUpdatePosition(qint64,qint64)));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    //Start new thread.
    workerThread->start();
}
