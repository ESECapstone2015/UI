/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *dot;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *Lbl_xangle;
    QLabel *Lbl_yangle;
    QLabel *Lbl_zangle;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 1000);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dot = new QLabel(centralWidget);
        dot->setObjectName(QStringLiteral("dot"));
        dot->setGeometry(QRect(500, 500, 16, 16));
        dot->setPixmap(QPixmap(QString::fromUtf8("../dot.png")));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 930, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 930, 47, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 930, 47, 13));
        Lbl_xangle = new QLabel(centralWidget);
        Lbl_xangle->setObjectName(QStringLiteral("Lbl_xangle"));
        Lbl_xangle->setGeometry(QRect(65, 930, 47, 13));
        Lbl_yangle = new QLabel(centralWidget);
        Lbl_yangle->setObjectName(QStringLiteral("Lbl_yangle"));
        Lbl_yangle->setGeometry(QRect(175, 930, 47, 13));
        Lbl_zangle = new QLabel(centralWidget);
        Lbl_zangle->setObjectName(QStringLiteral("Lbl_zangle"));
        Lbl_zangle->setGeometry(QRect(275, 930, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        dot->setText(QString());
        label->setText(QApplication::translate("MainWindow", "X Angle:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Y Angle:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Z Angle:", 0));
        Lbl_xangle->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Lbl_yangle->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Lbl_zangle->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
