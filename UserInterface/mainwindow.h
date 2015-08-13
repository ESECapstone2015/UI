#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define COMPORT "COM8"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void StartPolling();
    char *listCOM();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage image;

public slots:
    void onUpdatePosition(qint64 posx, qint64 posy, qint64 anglex, qint64 angley, qint64 anglez);
    void debugBox(QString msg);
};

#endif // MAINWINDOW_H
