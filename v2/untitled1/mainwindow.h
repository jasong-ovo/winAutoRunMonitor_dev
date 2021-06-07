#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void init_logon();
    void init_service();
    void init_driver();
    void init_task();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
