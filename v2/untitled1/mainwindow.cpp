#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <direct.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->logon, SIGNAL(clicked()), this, SLOT(init_logon()) );
    connect(ui->service, SIGNAL(clicked()), this, SLOT(init_service()) );
    connect(ui->driver, SIGNAL(clicked()), this, SLOT(init_driver()) );
    connect(ui->scheduledTask, SIGNAL(clicked()), this, SLOT(init_task()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_logon() {
    ui->infoTable->clear();
    QStringList strs = {"name", "include path", "verified"};
    ui->infoTable->setHorizontalHeaderLabels(strs);
    QTableWidgetItem *name;
    QTableWidgetItem *path;
    QTableWidgetItem *verifying;

    ui->infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoTable->setStyleSheet("border:none; selection-color:black; selection-background-color:#E6E6FA;");


    ifstream logonIn("..\\results\\logon_dir.txt");
    string line;
    int rows = 0;
    while (getline(logonIn, line)) {
        int tailName;
        int tailPath;
        int tailVerifying;

        tailName = line.find('\t');
        tailPath = line.find('\t', tailName+1);
        tailVerifying = line.size() - 1;
        //cout<<line.substr(0, tailName)<<line.substr(tailName+1, tailPath - tailName)<<line.substr(tailPath+1, tailVerifying- tailPath)<<endl;

        name = new QTableWidgetItem(tr(line.substr(0, tailName).c_str()));
        path = new QTableWidgetItem(tr(line.substr(tailName+1, tailPath - tailName).c_str()));
        verifying = new QTableWidgetItem(tr(line.substr(tailPath+1, tailVerifying- tailPath).c_str()));

        ui->infoTable->setRowCount(rows+1);
        ui->infoTable->setItem(rows, 0, name);
        ui->infoTable->setItem(rows, 1, path);
        ui->infoTable->setItem(rows, 2, verifying);
        rows ++;

    }


    ifstream logonIn_reg("..\\results\\logon_reg.txt");
    rows = 0;
    while (getline(logonIn_reg, line)) {
        int tailName;
        int tailPath;
        int tailVerifying;

        tailName = line.find('\t');
        tailPath = line.find('\t', tailName+1);
        tailVerifying = line.size() - 1;
        //cout<<line.substr(0, tailName)<<line.substr(tailName+1, tailPath - tailName)<<line.substr(tailPath+1, tailVerifying- tailPath)<<endl;

        name = new QTableWidgetItem(tr(line.substr(0, tailName).c_str()));
        path = new QTableWidgetItem(tr(line.substr(tailName+1, tailPath - tailName).c_str()));
        verifying = new QTableWidgetItem(tr(line.substr(tailPath+1, tailVerifying- tailPath).c_str()));

        ui->infoTable->setRowCount(rows+1);
        ui->infoTable->setItem(rows, 0, name);
        ui->infoTable->setItem(rows, 1, path);
        ui->infoTable->setItem(rows, 2, verifying);
        rows ++;

    }


}


void MainWindow::init_service() {
    ui->infoTable->clear();
    QStringList strs = {"name", "include path", "verified"};
    ui->infoTable->setHorizontalHeaderLabels(strs);
    QTableWidgetItem *name;
    QTableWidgetItem *path;
    QTableWidgetItem *verifying;

    ui->infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoTable->setStyleSheet("border:none; selection-color:black; selection-background-color:#E6E6FA;");


    ifstream serviceIn("..\\results\\service.txt");
    string line;
    int rows = 0;
    while (getline(serviceIn, line)) {
        int tailName;
        int tailPath;
        int tailVerifying;

        tailName = line.find('\t');
        tailPath = line.find('\t', tailName+1);
        tailVerifying = line.size() - 1;

        //cout<<line.substr(0, tailName)<<line.substr(tailName+1, tailPath - tailName)<<line.substr(tailPath+1, tailVerifying- tailPath)<<endl;

        name = new QTableWidgetItem(tr(line.substr(0, tailName).c_str()));
        path = new QTableWidgetItem(tr(line.substr(tailName+1, tailPath - tailName).c_str()));
        verifying = new QTableWidgetItem(tr(line.substr(tailPath+1, tailVerifying- tailPath).c_str()));

        ui->infoTable->setRowCount(rows+1);
        ui->infoTable->setItem(rows, 0, name);
        ui->infoTable->setItem(rows, 1, path);
        ui->infoTable->setItem(rows, 2, verifying);
        rows ++;

    }

}


void MainWindow::init_driver() {
    ui->infoTable->clear();
    QStringList strs = {"name", "include path", "verified"};
    ui->infoTable->setHorizontalHeaderLabels(strs);
    QTableWidgetItem *name;
    QTableWidgetItem *path;
    QTableWidgetItem *verifying;

    ui->infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoTable->setStyleSheet("border:none; selection-color:black; selection-background-color:#E6E6FA;");


    ifstream driverIn("..\\results\\driver.txt");
    string line;
    int rows = 0;
    while (getline(driverIn, line)) {
        int tailName;
        int tailPath;
        int tailVerifying;

        tailName = line.find('\t');
        tailPath = line.find('\t', tailName+1);
        tailVerifying = line.size() - 1;

        //cout<<line.substr(0, tailName)<<line.substr(tailName+1, tailPath - tailName)<<line.substr(tailPath+1, tailVerifying- tailPath)<<endl;

        name = new QTableWidgetItem(tr(line.substr(0, tailName).c_str()));
        path = new QTableWidgetItem(tr(line.substr(tailName+1, tailPath - tailName).c_str()));
        verifying = new QTableWidgetItem(tr(line.substr(tailPath+1, tailVerifying- tailPath).c_str()));

        ui->infoTable->setRowCount(rows+1);
        ui->infoTable->setItem(rows, 0, name);
        ui->infoTable->setItem(rows, 1, path);
        ui->infoTable->setItem(rows, 2, verifying);
        rows ++;

    }

}


void MainWindow::init_task() {
    ui->infoTable->clear();
    QStringList strs = {"name", "include path", "verified"};
    ui->infoTable->setHorizontalHeaderLabels(strs);
    QTableWidgetItem *name;
    QTableWidgetItem *path;
    QTableWidgetItem *verifying;

    ui->infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoTable->setStyleSheet("border:none; selection-color:black; selection-background-color:#E6E6FA;");


    ifstream taskIn("..\\results\\task.txt");
    string line;
    int rows = 0;
    while (getline(taskIn, line)) {
        int tailName;
        int tailPath;
        int tailVerifying;

        tailName = line.find('\t');
        tailPath = line.find('\t', tailName+1);
        tailVerifying = line.size() - 1;

        //cout<<line.substr(0, tailName)<<line.substr(tailName+1, tailPath - tailName)<<line.substr(tailPath+1, tailVerifying- tailPath)<<endl;

        name = new QTableWidgetItem(tr(line.substr(0, tailName).c_str()));
        path = new QTableWidgetItem(tr(line.substr(tailName+1, tailPath - tailName).c_str()));
        verifying = new QTableWidgetItem(tr(line.substr(tailPath+1, tailVerifying- tailPath).c_str()));

        ui->infoTable->setRowCount(rows+1);
        ui->infoTable->setItem(rows, 0, name);
        ui->infoTable->setItem(rows, 1, path);
        ui->infoTable->setItem(rows, 2, verifying);
        rows ++;

    }

}
