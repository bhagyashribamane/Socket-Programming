#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpcilent.h"
#include <QDateTime>
#include<QMessageBox>
#include<QTcpSocket>
#include <QTableWidgetItem>
#include <QDebug>

#include<QSqlDatabase>
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
    connect(ui->btn_connectCamera1, &QPushButton::clicked, this, &MainWindow::onBtnConnectCam1);
    connect(ui->btn_connectCamera2, &QPushButton::clicked, this, &MainWindow::onBbtnConnectCam2);

    // Disconnected BUtton
    connect(ui->btn_Disconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectedButton);

    // learn button
    connect(ui->btn_Learn, &QPushButton::clicked, this, &MainWindow::onLearnButton);
    connect(this, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);


    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"Actual Data","Identifier", "length","Parsed Value", "HEX", "Timestamp"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

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

    if(ip.isEmpty()){
        QMessageBox::warning(this , "error", "Enter IP Address");
        return;
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

    if(ip.isEmpty()){
        QMessageBox::warning(this, "Error","Enter IP Address");
        return;
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
    if(activeCamera == "CAM1")
        Cam1cilent->disconnectCamera();
    else if(activeCamera == "CAM2")
        Cam2cilent->disconnectCamera();
       qDebug()<<"Disconnected Camera 2";
}

void MainWindow::onLearnButton()
{
    learnDialog->show();
}


void MainWindow::onClickError(QString message)
{
  statusBar()->showMessage(message, 5000);
}



