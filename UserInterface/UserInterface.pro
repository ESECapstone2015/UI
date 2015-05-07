#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T13:21:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UserInterface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Serial.cpp \
    pollingthread.cpp

HEADERS  += mainwindow.h \
    Serial.h \
    pollingthread.h

FORMS    += mainwindow.ui
