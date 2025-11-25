#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpcilent.h"
#include <QDateTime>
#include <QTableWidgetItem>
#include <QDebug>

// #include<QSqlDatabase>

struct ParsedPacket{
    QString command;
    int length;
    QString value;

};
ParsedPacket parsePacket(const QString &data){
    ParsedPacket p;
    if(data.length()>=6){
        p.command=data.mid(0,2);
        p.length=data.mid(2,4).toInt();
        p.value=data.mid(6);
    }
    return p;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    cilent = new TcpClient(this);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"Actual Data","Identifier", "length","Parsed Value", "HEX", "Timestamp"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    connect(cilent, &TcpClient::dataReceived, this, &MainWindow::onDataRecevied);
    connect(cilent, &TcpClient::errorOccurred, this, &MainWindow::onClickError);

    connect(ui->btn_connect, &QPushButton::clicked, this, &MainWindow::onConnectedButton);
    connect(ui->btn_Disconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectedButton);

    learnDialog = new LearnDialog(this);
    // connect(ui->btn_Learn, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);
    connect(ui->btn_Learn, &QPushButton::clicked, this, &MainWindow::onLearnButton);
    connect(this, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);


     // qDebug() << "Available SQL Drivers:" << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDataRecevied(QString ascii, QString hex)
{
    ParsedPacket packet = parsePacket(ascii);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ascii));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(packet.command));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString ::number(packet.length)));
     ui->tableWidget->setItem(row, 3, new QTableWidgetItem(packet.value));
     ui->tableWidget->setItem(row, 4, new QTableWidgetItem(hex));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(time));

    ui->tableWidget->scrollToBottom();

    emit newDataAvailable(ascii);
}

void MainWindow::onConnectedButton()
{
    cilent->connectToCamera(ui->lineEdit->text(), ui->lineEdit_2->text().toUInt());
}

void MainWindow::onDisconnectedButton()
{
    cilent->disconnectCamera();
}

void MainWindow::onLearnButton()
{
    learnDialog->show();
}


void MainWindow::onClickError(QString message)
{
  statusBar()->showMessage(message, 5000);
}



