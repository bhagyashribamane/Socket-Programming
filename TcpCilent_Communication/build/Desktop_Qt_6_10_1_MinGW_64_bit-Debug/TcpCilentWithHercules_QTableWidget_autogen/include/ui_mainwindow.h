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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_8;
    QGridLayout *gridLayout;
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
    QComboBox *comboBox;
    QPushButton *CameraStartBtn;
    QPushButton *CameraStopBtn;
    QPushButton *LearnBtn;
    QPushButton *btn_Learn;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *lineEdit_TotalCount;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_GoodCount;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_BadCount;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_8 = new QHBoxLayout(centralwidget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
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


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

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


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_3->addWidget(comboBox);

        CameraStartBtn = new QPushButton(centralwidget);
        CameraStartBtn->setObjectName("CameraStartBtn");

        horizontalLayout_3->addWidget(CameraStartBtn);

        CameraStopBtn = new QPushButton(centralwidget);
        CameraStopBtn->setObjectName("CameraStopBtn");

        horizontalLayout_3->addWidget(CameraStopBtn);

        LearnBtn = new QPushButton(centralwidget);
        LearnBtn->setObjectName("LearnBtn");

        horizontalLayout_3->addWidget(LearnBtn);

        btn_Learn = new QPushButton(centralwidget);
        btn_Learn->setObjectName("btn_Learn");

        horizontalLayout_3->addWidget(btn_Learn);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        horizontalLayout_6->addWidget(label_7);

        lineEdit_TotalCount = new QLineEdit(centralwidget);
        lineEdit_TotalCount->setObjectName("lineEdit_TotalCount");

        horizontalLayout_6->addWidget(lineEdit_TotalCount);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        lineEdit_GoodCount = new QLineEdit(centralwidget);
        lineEdit_GoodCount->setObjectName("lineEdit_GoodCount");

        horizontalLayout_4->addWidget(lineEdit_GoodCount);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        lineEdit_BadCount = new QLineEdit(centralwidget);
        lineEdit_BadCount->setObjectName("lineEdit_BadCount");

        horizontalLayout_5->addWidget(lineEdit_BadCount);


        horizontalLayout_7->addLayout(horizontalLayout_5);


        gridLayout->addLayout(horizontalLayout_7, 4, 0, 1, 1);


        horizontalLayout_8->addLayout(gridLayout);

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
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Camera 1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Camera 2", nullptr));

        CameraStartBtn->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        CameraStopBtn->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        LearnBtn->setText(QCoreApplication::translate("MainWindow", "Learn", nullptr));
        btn_Learn->setText(QCoreApplication::translate("MainWindow", "Show Result", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Total Count", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Good Count", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Bad Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
