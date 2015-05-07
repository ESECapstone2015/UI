#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void StartPolling();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void onUpdatePosition(qint64 posx, qint64 posy);
    void debugBox(QString msg);
};

#endif // MAINWINDOW_H
