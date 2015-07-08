// Some code borrowed from http://stackoverflow.com/questions/14545961/modify-qt-gui-from-background-worker-thread
// Written by Mark Mahony, May 1st, 2015
// Polls serial port for new position data, then updates dot on screen based on data.

#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pollingthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if (!image.load("C:\\test.jpg"))
    {
        qDebug("Error loading picture.");
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onUpdatePosition(qint64 posx, qint64 posy, qint64 anglex, qint64 angley, qint64 anglez){
    ui->dot->setPixmap(QPixmap::fromImage(image.copy(posy, posx, posy + 640, posx + 480)));
    ui->Lbl_xangle->setText(QString::number(anglex));
    ui->Lbl_yangle->setText(QString::number(angley));
    ui->Lbl_zangle->setText(QString::number(anglez));
    ui->Lbl_xpos->setText(QString::number(posx));
    ui->Lbl_ypos->setText(QString::number(posy));
}

void MainWindow::debugBox(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::StartPolling(){
    //Create worker thread.
    QThread* thread = new QThread;
    PollingThread* workerThread = new PollingThread ();

    //Connect slots and signals to update dot position.
    // Start polling after thread start.
    connect(thread,
            SIGNAL(started()),
            workerThread,
            SLOT(pollPort()));
    // Update position form telemetry data.
    connect(workerThread,
            SIGNAL(updatePosition(qint64,qint64,qint64,qint64,qint64)),
            this,
            SLOT(onUpdatePosition(qint64,qint64,qint64,qint64,qint64)));
    // Send debug message.
    connect(workerThread,
            SIGNAL(sendDebug(QString)),
            this,
            SLOT(debugBox(QString)));
    // For Testing purposes, makes sure signals are firing.
    /*connect(workerThread,
            SIGNAL(sendDebug(QString)),
            qApp,
            SLOT(aboutQt()));*/
    // Start new thread.

    workerThread->moveToThread(thread);

    qDebug("Starting Thread");

    thread->start();
}
