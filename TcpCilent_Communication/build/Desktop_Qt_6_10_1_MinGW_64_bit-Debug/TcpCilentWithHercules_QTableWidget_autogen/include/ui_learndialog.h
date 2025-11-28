/********************************************************************************
** Form generated from reading UI file 'learndialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNDIALOG_H
#define UI_LEARNDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LearnDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditLearnValue;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lbl_good;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lbl_bad;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lbl_total;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *teach;
    QPushButton *clear;
    QPushButton *close;
    QPushButton *disconnect;

    void setupUi(QDialog *LearnDialog)
    {
        if (LearnDialog->objectName().isEmpty())
            LearnDialog->setObjectName("LearnDialog");
        LearnDialog->resize(707, 509);
        verticalLayout_2 = new QVBoxLayout(LearnDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(LearnDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEditLearnValue = new QLineEdit(LearnDialog);
        lineEditLearnValue->setObjectName("lineEditLearnValue");

        horizontalLayout->addWidget(lineEditLearnValue);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(LearnDialog);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        lbl_good = new QLineEdit(LearnDialog);
        lbl_good->setObjectName("lbl_good");

        horizontalLayout_5->addWidget(lbl_good);


        horizontalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_6 = new QLabel(LearnDialog);
        label_6->setObjectName("label_6");

        horizontalLayout_6->addWidget(label_6);

        lbl_bad = new QLineEdit(LearnDialog);
        lbl_bad->setObjectName("lbl_bad");

        horizontalLayout_6->addWidget(lbl_bad);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(LearnDialog);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        lbl_total = new QLineEdit(LearnDialog);
        lbl_total->setObjectName("lbl_total");

        horizontalLayout_7->addWidget(lbl_total);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout->addLayout(horizontalLayout_8);

        tableWidget = new QTableWidget(LearnDialog);
        tableWidget->setObjectName("tableWidget");

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        teach = new QPushButton(LearnDialog);
        teach->setObjectName("teach");

        horizontalLayout_9->addWidget(teach);

        clear = new QPushButton(LearnDialog);
        clear->setObjectName("clear");

        horizontalLayout_9->addWidget(clear);

        close = new QPushButton(LearnDialog);
        close->setObjectName("close");

        horizontalLayout_9->addWidget(close);

        disconnect = new QPushButton(LearnDialog);
        disconnect->setObjectName("disconnect");

        horizontalLayout_9->addWidget(disconnect);


        verticalLayout->addLayout(horizontalLayout_9);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LearnDialog);

        QMetaObject::connectSlotsByName(LearnDialog);
    } // setupUi

    void retranslateUi(QDialog *LearnDialog)
    {
        LearnDialog->setWindowTitle(QCoreApplication::translate("LearnDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LearnDialog", "Learned Value", nullptr));
        label_5->setText(QCoreApplication::translate("LearnDialog", "Good", nullptr));
        label_6->setText(QCoreApplication::translate("LearnDialog", "Bad", nullptr));
        label_7->setText(QCoreApplication::translate("LearnDialog", "Total", nullptr));
        teach->setText(QCoreApplication::translate("LearnDialog", "Teach", nullptr));
        clear->setText(QCoreApplication::translate("LearnDialog", "Clear", nullptr));
        close->setText(QCoreApplication::translate("LearnDialog", "Close", nullptr));
        disconnect->setText(QCoreApplication::translate("LearnDialog", "DisConnectCameras", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearnDialog: public Ui_LearnDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNDIALOG_H
