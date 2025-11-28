#include "learndialog.h"
#include "ui_learndialog.h"
#include "database_manager.h"
#include <QMessageBox>
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
      connect(ui->disconnect, &QPushButton::clicked,this,&LearnDialog::DisConnected);
}

LearnDialog::~LearnDialog()
{
    delete ui;
}

void LearnDialog::setDatabaseManager(DataBase_Manager *db)
{
    dbManager=db;

}
// This function is called whenever a new value is received from the main window (or the camera).
// value is the data string that you want to compare with the "taught value".
void LearnDialog::IncomingValue(QString value)
{
    totalCount++; //Keeps track of how many values have been received in total.Every new incoming value increments this counter by 1.

    bool match = (!taughtValue.isEmpty() && value == taughtValue);
// Checks whether the incoming value matches the taught value
    // Updates counters based on the comparison result:
    // If match is true → increment goodCount (value is correct)
    // If match is false → increment badCount (value is incorrect)
    if(match)
        goodCount++;
    else
        badCount++;



   // Adds the received value to a history table in the Learn Dialog.
    //The table stores the timestamp, value, and whether it was "Good" or "Bad".
    // Only shows the last 10 values (older rows are removed).
    addToHistory(value, match);

    // Updates the UI labels to show the current Good, Bad, and Total counts.
    updateCounters();
}

// This function is called when the Teach button in the Learn Dialog is clicked.
void LearnDialog::TeachClicked()
{

    qDebug()<<"Teach Button is performmed";
    // Checks if the table showing received values is empty.If there are no rows, there’s nothing to teach, so the function exits early.
    if(ui->tableWidget->rowCount()==0)
        return;

    //Selects the last row of the table (rowCount() - 1) to use as the taught value.Column 1 contains the actual value/identifier from the parsed packet.
    taughtValue=ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->text();
    ui->lineEditLearnValue->setText(taughtValue);

    emit learnValueChanged(taughtValue);
}

// This function is executed when the user clicks the Clear button.
void LearnDialog::ClearClicked()
{
    // This removes the currently stored learned value.
    taughtValue.clear();
    // This sets all counters back to zero.
    goodCount= badCount=totalCount=0;

    ui->tableWidget->setRowCount(0);
    updateCounters();
    ui->lineEditLearnValue->clear();

    emit goodCountUpdated(goodCount);
    emit badCountUpdated(badCount);
}

void LearnDialog::closeClicked()
{
    close();
}

void LearnDialog::DisConnected()
{
    QMessageBox::information(this, "Disconnect", "Disconnecting cameras and saving job data...");

    emit requestDisconnect();

    close();
}
// This function updates the UI labels so the latest Good, Bad, and Total counts are shown correctly on the screen.
void LearnDialog::updateCounters()
{
    ui->lbl_good->setText(QString("Good: %1").arg(goodCount));
    ui->lbl_bad->setText(QString("Bad: %1").arg(badCount));
    ui->lbl_total->setText(QString("Total: %1").arg(totalCount));
}
// This function adds the scanned value to a table and marks it as Good or Bad, while keeping only last 10 records.
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

