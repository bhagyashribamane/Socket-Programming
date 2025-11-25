#include "learndialog.h"
#include <QMessageBox>
#include "ui_learndialog.h"
#include<QDateTime>
#include<QDebug>

LearnDialog::LearnDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearnDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"timestamp", "value","status"});
     ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->lineEditLearnValue->setReadOnly(true);
     updateCounters();

      connect(ui->teach, &QPushButton::clicked, this, &LearnDialog::TeachClicked);
      connect(ui->clear, &QPushButton::clicked, this , &LearnDialog::ClearClicked);
      connect(ui->close, &QPushButton::clicked, this , &LearnDialog::closeClicked);
}

LearnDialog::~LearnDialog()
{
    delete ui;
}

void LearnDialog::IncomingValue(QString value)
{
    totalCount++;

    bool match = (!taughtValue.isEmpty() && value == taughtValue);

    if(match)
        goodCount++;
    else
        badCount++;

    addToHistory(value, match);
    updateCounters();
}

void LearnDialog::TeachClicked()
{

    qDebug()<<"Teach Button is performmed";
    if(ui->tableWidget->rowCount()==0)
        return;

    taughtValue=ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->text();
    ui->lineEditLearnValue->setText(taughtValue);

    emit learnValueChanged(taughtValue);


}

void LearnDialog::ClearClicked()
{
    taughtValue.clear();
    goodCount= badCount=totalCount=0;
    ui->tableWidget->setRowCount(0);
    updateCounters();
    ui->lineEditLearnValue->clear();
}

void LearnDialog::closeClicked()
{
    close();
}

void LearnDialog::updateCounters()
{
    ui->lbl_good->setText(QString("Good: %1").arg(goodCount));
    ui->lbl_bad->setText(QString("Bad: %1").arg(badCount));
    ui->lbl_total->setText(QString("Total: %1").arg(totalCount));

}

void LearnDialog::addToHistory(QString value, bool isMatch)
{
    if(ui->tableWidget->rowCount()>=10)
        ui->tableWidget->removeRow(0);

    int row=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

     QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui->tableWidget->setItem(row,0, new QTableWidgetItem(timestamp));
     ui->tableWidget->setItem(row,1,new QTableWidgetItem(value));
    ui->tableWidget->setItem(row,2, new QTableWidgetItem(isMatch ? "Good": "Bad"));


}

