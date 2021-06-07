/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *logon;
    QPushButton *service;
    QPushButton *driver;
    QPushButton *scheduledTask;
    QTableWidget *infoTable;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(2637, 1777);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 2711, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        logon = new QPushButton(horizontalLayoutWidget);
        logon->setObjectName(QStringLiteral("logon"));

        horizontalLayout->addWidget(logon);

        service = new QPushButton(horizontalLayoutWidget);
        service->setObjectName(QStringLiteral("service"));

        horizontalLayout->addWidget(service);

        driver = new QPushButton(horizontalLayoutWidget);
        driver->setObjectName(QStringLiteral("driver"));

        horizontalLayout->addWidget(driver);

        scheduledTask = new QPushButton(horizontalLayoutWidget);
        scheduledTask->setObjectName(QStringLiteral("scheduledTask"));

        horizontalLayout->addWidget(scheduledTask);

        infoTable = new QTableWidget(centralWidget);
        if (infoTable->columnCount() < 3)
            infoTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        infoTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        infoTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        infoTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (infoTable->rowCount() < 1)
            infoTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        infoTable->setItem(0, 0, __qtablewidgetitem4);
        infoTable->setObjectName(QStringLiteral("infoTable"));
        infoTable->setGeometry(QRect(0, 40, 2641, 1741));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        MainWindow->insertToolBarBreak(mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        logon->setText(QApplication::translate("MainWindow", "logon", Q_NULLPTR));
        service->setText(QApplication::translate("MainWindow", "service", Q_NULLPTR));
        driver->setText(QApplication::translate("MainWindow", "driver", Q_NULLPTR));
        scheduledTask->setText(QApplication::translate("MainWindow", "scheduled task", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = infoTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = infoTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "image path", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = infoTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "verified", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = infoTable->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));

        const bool __sortingEnabled = infoTable->isSortingEnabled();
        infoTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = infoTable->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        infoTable->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
