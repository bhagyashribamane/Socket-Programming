/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEditProductName;
    QLabel *label_4;
    QLineEdit *lineEditTaughtVAlue;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditIP;
    QLabel *label_2;
    QLineEdit *lineEditPort;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Cam1Btn;
    QPushButton *Cam2Btn;
    QPushButton *btn_Disconnect;
    QPushButton *btn_Learn;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        lineEditProductName = new QLineEdit(centralwidget);
        lineEditProductName->setObjectName("lineEditProductName");

        horizontalLayout->addWidget(lineEditProductName);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        lineEditTaughtVAlue = new QLineEdit(centralwidget);
        lineEditTaughtVAlue->setObjectName("lineEditTaughtVAlue");

        horizontalLayout->addWidget(lineEditTaughtVAlue);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEditIP = new QLineEdit(centralwidget);
        lineEditIP->setObjectName("lineEditIP");

        horizontalLayout_2->addWidget(lineEditIP);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEditPort = new QLineEdit(centralwidget);
        lineEditPort->setObjectName("lineEditPort");

        horizontalLayout_2->addWidget(lineEditPort);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Cam1Btn = new QPushButton(centralwidget);
        Cam1Btn->setObjectName("Cam1Btn");

        horizontalLayout_3->addWidget(Cam1Btn);

        Cam2Btn = new QPushButton(centralwidget);
        Cam2Btn->setObjectName("Cam2Btn");

        horizontalLayout_3->addWidget(Cam2Btn);

        btn_Disconnect = new QPushButton(centralwidget);
        btn_Disconnect->setObjectName("btn_Disconnect");

        horizontalLayout_3->addWidget(btn_Disconnect);

        btn_Learn = new QPushButton(centralwidget);
        btn_Learn->setObjectName("btn_Learn");

        horizontalLayout_3->addWidget(btn_Learn);


        verticalLayout->addLayout(horizontalLayout_3);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");

        verticalLayout->addWidget(tableWidget);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Product Name", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Taught Value", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port Number", nullptr));
        Cam1Btn->setText(QCoreApplication::translate("MainWindow", "Camera1 Connect", nullptr));
        Cam2Btn->setText(QCoreApplication::translate("MainWindow", "Camera 2 Connaect", nullptr));
        btn_Disconnect->setText(QCoreApplication::translate("MainWindow", "DisConnect", nullptr));
        btn_Learn->setText(QCoreApplication::translate("MainWindow", "Learn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
