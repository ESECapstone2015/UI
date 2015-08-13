// Some code borrowed from http://stackoverflow.com/questions/14545961/modify-qt-gui-from-background-worker-thread
// Written by Mark Mahony, May 1st, 2015
// Polls serial port for new position data, then updates dot on screen based on data.

#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include <QSignalMapper>
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

    QSignalMapper * mapper = new QSignalMapper(this);

    // Set up signal mapper to pass argument to new thread.
    connect(mapper,
            SIGNAL(mapped(QString)),
            workerThread,
            SLOT(pollPort(QString)));

    mapper->setMapping(thread, comPort);

    //Connect slots and signals to update dot position.
    // Start polling after thread start.
    connect(thread,
            SIGNAL(started()),
            mapper,
            SLOT(map()));


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
char * MainWindow::listCOM()
{
    char path[5000]; // buffer to store the path of the COMPORTS
    //char name[7]; //Large enough for "COM100\0"
    char list[256];	// Return list.
    DWORD test;
    bool gotPort = 0; // in case the port is not found

/*
    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        sprintf_s(name, "COM%d", i);

        test = QueryDosDevice((LPCWSTR)name, (LPWSTR) path, sizeof(path));

        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
            gotPort = TRUE;
            list[i] = 1;
            ui->comBx->addItem("COM" + i);
        }
        else
        {
            list[i] = 0;
        }
    }*/

    test = QueryDosDevice(NULL, (LPWSTR) path, sizeof(path));

    for (int i = 0; i < 255; i++)
    {
        // Test the return value and error if any
        if (sscanf_s(path, "COM%d", i) == 1) //QueryDosDevice returns zero if it didn't find an object
        {
            gotPort = TRUE;
            ui->comBx->addItem("COM" + i);
        }
    }


    if (gotPort)
    {
        QMessageBox msgBox;
        msgBox.setText("Found port");
        msgBox.exec();
        return list;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8(path));
        msgBox.exec();
        return NULL;
    }
}
