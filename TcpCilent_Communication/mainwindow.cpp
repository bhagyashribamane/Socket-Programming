#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpcilent.h"
#include <QDateTime>
#include<QMessageBox>
#include<QTcpSocket>
#include <QTableWidgetItem>
#include <QDebug>
#include<QStatusBar>
// It defines a data structure to store a
// parsed version of the raw data received from the camera.When the camera sends data like RD00041234
struct ParsedPacket{
    QString command;
    int length;
    QString value;

};
// parsepacket is function name
// mid() is used to cut the string into meaningful parts based on known positions. It’s simple and precise for parsing structured data.
ParsedPacket parsePacket(const QString &data){
    ParsedPacket p; //Creates a new ParsedPacket object called p. This will store the parsed parts of the data.
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

    Cam1cilent = new TcpClient(this);
    Cam2cilent=new TcpClient(this);

    // we are creating an instance of the LearnDialog class.
    learnDialog = new LearnDialog(this);

    // learnDialog = new LearnDialog(this);
    learnDialog->setDatabaseManager(dbManager);

    dbManager = new DataBase_Manager(this);
    if(dbManager->connectDatabase())
        qDebug() << "Database Ready";
    else
        qDebug() << "Database Not Connected";


    // data received
    connect(Cam1cilent, &TcpClient::dataReceived, this, &MainWindow::onDataRecevied);
     connect(Cam2cilent, &TcpClient::dataReceived, this, &MainWindow::onDataRecevied);

     // error checking
    connect(Cam1cilent, &TcpClient::errorOccurred, this, &MainWindow::onClickError);
    connect(Cam2cilent, &TcpClient::errorOccurred, this, &MainWindow::onClickError);

    // connection
    connect(ui->Cam1Btn, &QPushButton::clicked, this, &MainWindow::onBtnConnectCam1);
    connect(ui->Cam2Btn, &QPushButton::clicked, this, &MainWindow::onBbtnConnectCam2);

    // Disconnected BUtton
    connect(ui->btn_Disconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectedButton);

    // learn button
    connect(ui->btn_Learn, &QPushButton::clicked, this, &MainWindow::onLearnButton);
    connect(this, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);
    connect(learnDialog, &LearnDialog::requestDisconnect, this, &MainWindow::handleDisconnect);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"Actual Data","Identifier", "length","Parsed Value", "HEX", "Timestamp"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);


    connect(learnDialog, &LearnDialog::goodCountUpdated, this, [&](int count){
        if(activeCamera == "CAM1") goodCountCAM1 = count;
        else if(activeCamera == "CAM2") goodCountCAM2 = count;
    });

    connect(learnDialog, &LearnDialog::badCountUpdated, this, [&](int count){
        if(activeCamera == "CAM1") badCountCAM1 = count;
        else if(activeCamera == "CAM2") badCountCAM2 = count;
    });
// qDebug() << "Available SQL Drivers:" << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnConnectCam1()
{
    QString ip= ui->lineEditIP->text();
    int port=ui->lineEditPort->text().toInt();

    QString productName = ui->lineEditProductName->text();
    QString TaughtValue=ui->lineEditTaughtVAlue->text();
    if(productName.isEmpty() || TaughtValue.isEmpty() ) {
        QMessageBox::warning(this,"Missing Data","Enter Product Name And Taught Value");
        return;
    }

    if(ip.isEmpty()){
        QMessageBox::warning(this , "error", "Enter IP Address");
        return;
    }

    activeCamera="CAM1";
    startTime=QDateTime::currentDateTime();

    jobIdCAM1 =  dbManager->insertjob(productName, TaughtValue , activeCamera, startTime.date());
    if(jobIdCAM1==-1){
        QMessageBox::warning(this, "error","DataBase Error, Failed Insert Job");
    }

    // This line tells your TcpClient object (cam1Client) to start connecting to the camera using the IP address and port number
    // entered by the user.
    Cam1cilent->connectToCamera(ip,port);
    qDebug()<<"Camera 1 Connected"<<ip<<port;


}
void MainWindow::onBbtnConnectCam2()
{
    QString ip= ui->lineEditIP->text();
    int port = ui->lineEditPort->text().toInt();

    QString productName = ui->lineEditProductName->text();
    QString TaughtValue=ui->lineEditTaughtVAlue->text();
    if(productName.isEmpty() || TaughtValue.isEmpty() ) {
        QMessageBox::warning(this,"Missing Data","Enter Product Name And Taught Value");
        return;
    }


    if(ip.isEmpty()){
        QMessageBox::warning(this, "Error","Enter IP Address");
        return;
    }

    activeCamera="CAM2";
    startTime=QDateTime::currentDateTime();

    jobIdCAM2 =  dbManager->insertjob(productName, TaughtValue , activeCamera, startTime.date());
    if(jobIdCAM2==-1){
        QMessageBox::warning(this, "error","DataBase Error , Failed Isert Job");
    }


    Cam2cilent->connectToCamera(ip,port);
    qDebug()<<"Camera 2 Connected"<<ip<<port;
}

 // This function is called whenever new data is received from the camera.
void MainWindow::onDataRecevied(QString ascii, QString hex)
{

    // The raw data from the camera is in ASCII format, e.g., "RD00041234".
    // parsePacket() extracts parts of the data:
    // packet now holds these structured pieces of data.
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


    // Because your MainWindow receives camera data first, but your LearnDialog also needs that same data.
    emit newDataAvailable(ascii);
}


void MainWindow::onDisconnectedButton()
{
    stopTime=QDateTime::currentDateTime();
    Cam1cilent->disconnectCamera();

    if(activeCamera=="CAM1"){
        dbManager->updateJob(jobIdCAM1,goodCountCAM1,badCountCAM1,stopTime);
    }
    else if(activeCamera=="CAM2"){
        dbManager->updateJob(jobIdCAM2,goodCountCAM2,badCountCAM2,stopTime);
    }

    QMessageBox::information(this, "Job Saved", "Camera disconnected & job stored.");

    ui->statusbar->showMessage("Disconnected");

    activeCamera.clear();
}

void MainWindow::onLearnButton()
{
    learnDialog->show();
}


void MainWindow::onClickError(QString message)
{
  statusBar()->showMessage(message, 5000);
}

void MainWindow::handleDisconnect()
{
    qDebug() << "Handling disconnect from LearnDialog";

    // Disconnect Camera 1
    if(Cam1cilent && Cam1cilent->isConnected()) {
        Cam1cilent->disconnectCamera();
        stopTime = QDateTime::currentDateTime();
        dbManager->updateJob(jobIdCAM1, goodCountCAM1, badCountCAM1, stopTime);
        qDebug() << "Camera 1 Job Updated!";
    }

    // Disconnect Camera 2
    if(Cam2cilent && Cam2cilent->isConnected()) {
        Cam2cilent->disconnectCamera();
        stopTime = QDateTime::currentDateTime();
        dbManager->updateJob(jobIdCAM2, goodCountCAM2, badCountCAM2, stopTime);
        qDebug() << "Camera 2 Job Updated!";
    }

    QMessageBox::information(this, "Disconnected",
                             "Cameras disconnected and job stored successfully!");

}



