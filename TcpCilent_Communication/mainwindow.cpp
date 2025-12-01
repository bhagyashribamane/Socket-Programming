#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpcilent.h"
#include <QDateTime>
#include<QMessageBox>
#include<QTcpSocket>
#include <QTableWidgetItem>
#include <QDebug>
#include<QStatusBar>
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

    selectedCamera = "Camera 1";
    activeCamera = "";

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
    // connect(ui->CameraStopBtn, &QPushButton::clicked, this, &MainWindow::onBtnConnectCam1);
    // connect(ui->CameraStartBtn, &QPushButton::clicked, this, &MainWindow::onBbtnConnectCam2);

    // Disconnected BUtton
    connect(learnDialog, &LearnDialog::goodCountUpdated, this, [&](int count){
        if(activeCamera == "CAM1") goodCountCAM1 = count;
        else if(activeCamera == "CAM2") goodCountCAM2 = count;
    });

    connect(learnDialog, &LearnDialog::badCountUpdated, this, [&](int count){
        if(activeCamera == "CAM1") badCountCAM1 = count;
        else if(activeCamera == "CAM2") badCountCAM2 = count;
    });

    connect(learnDialog, &LearnDialog::requestDisconnect, this, &MainWindow::handleDisconnect);

    // learn button
    connect(ui->btn_Learn, &QPushButton::clicked, this, &MainWindow::onLearnButton);
    connect(this, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);
    connect(learnDialog, &LearnDialog::requestDisconnect, this, &MainWindow::handleDisconnect);

    connect(learnDialog, &LearnDialog::sendTeachData,this, &MainWindow::storeTeachValue);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels({"Actual Data","Identifier", "length","Parsed Value","HEX","Compare Value","Result","Timestamp"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);


    // QComboBox cameras
    connect(ui->comboBox, &QComboBox::currentTextChanged, this ,&MainWindow::onCameraChanged);
    connect(ui->CameraStartBtn,&QPushButton::clicked, this , &MainWindow::onStartCameras);
    connect(ui->CameraStopBtn,&QPushButton::clicked, this , &MainWindow::onStopCameras);

// qDebug() << "Available SQL Drivers:" << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}
 // This function is called whenever new data is received from the camera.
void MainWindow::onDataRecevied(QString ascii, QString hex)
{
    // The raw data from the camera is in ASCII format, e.g., "RD00041234".
    // parsePacket() extracts parts of the data:
    // packet now holds these structured pieces of data.
    ParsedPacket packet = parsePacket(ascii);

    // compare good or bad result
    double readValue=packet.value.toDouble();
    double CompareValue=ui->lineEditTaughtVAlue->text().toDouble();
    bool isMatch=(qAbs(readValue-CompareValue)<=5);


    updateTableWithPacket(packet, ascii, hex,isMatch);


    // Because your MainWindow receives camera data first, but your LearnDialog also needs that same data.
    emit newDataAvailable(ascii);

}
void MainWindow::updateTableWithPacket(const ParsedPacket &packet, const QString &ascii, const QString &hex , bool isMatch)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ascii));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(packet.command));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString ::number(packet.length)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(packet.value));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(hex));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(ui->lineEditTaughtVAlue->text()));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(isMatch ? "GOOD" : "BAD"));
    ui->tableWidget->setItem(row,7, new QTableWidgetItem(time));


    ui->tableWidget->scrollToBottom();
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
    stopTime = QDateTime::currentDateTime();

    if(Cam1cilent) Cam1cilent->disconnectCamera();
    if(Cam2cilent) Cam2cilent->disconnectCamera();

    if(activeCamera == "CAM1") {
        dbManager->updateJob(jobIdCAM1, goodCountCAM1, badCountCAM1, stopTime);
        qDebug() << "CAM1 Job Saved:" << "Good Count"<<goodCountCAM1 <<"BadCount"<< badCountCAM1;
    }
    else if(activeCamera == "CAM2") {
        dbManager->updateJob(jobIdCAM2, goodCountCAM2, badCountCAM2, stopTime);
        qDebug() << "CAM2 Job Saved:" <<"Good Count"<< goodCountCAM2 <<"BadCount"<< badCountCAM2;
    }

    QMessageBox::information(this, "Saved", "Camera disconnected & data stored.");
    activeCamera.clear();

}

void MainWindow::storeTeachValue(QString cameraValue, QString result)
{
    QString ProductName=ui->lineEditProductName->text().trimmed().replace(" ","_");
    if(ProductName.isEmpty()){
        QMessageBox::warning(this,"error","product are missing");
        return ;
    }
    if(!dbManager->insertCameraData(ProductName,cameraValue,result)){
        QMessageBox::warning(this,"db error","Failed");
    }else{
        qDebug()<<"Stored table:"<<ProductName<<"value:"<<cameraValue<<"result:"<<result;
    }

}

void MainWindow::onCameraChanged(const QString &camera)
{
    selectedCamera=camera;
    if(camera == "Camera 1"){
        if(Cam2cilent && Cam2cilent->isConnected()){
            Cam2cilent->disconnectCamera();
        }
        statusBar()->showMessage("Camera 1 Selected");
    }
    else if(camera=="Camera 2"){

        if(Cam1cilent && Cam1cilent->isConnected()){
        Cam1cilent->disconnected();
    }
    statusBar()->showMessage("camera 2 Selected");
}
}

void MainWindow::onStartCameras()
{
    QString ip=ui->lineEditIP->text();
    int port = ui->lineEditPort->text().toInt();

    if(ip.isEmpty()){
        QMessageBox::warning(this, "Ip Error","Enter Ip Address");
        return;
    }
    startTime=QDateTime::currentDateTime();

    if(selectedCamera=="Camera 1"){
        activeCamera="CAM1";
        Cam1cilent->connectToCamera(ip,port);
        statusBar()->showMessage("Connecting Camera 1...");
    }
    else if(selectedCamera=="Camera 2"){
        activeCamera="CAM2";
        Cam2cilent->connectToCamera(ip,port);
        statusBar()->showMessage("Cannecting Camera 2...");
    }
    else{
        QMessageBox::warning(this, "camera error", "Select cameraa");
    }
}

void MainWindow::onStopCameras()
{
    stopTime=QDateTime::currentDateTime();

    if(activeCamera=="CAM1"){
        Cam1cilent->disconnectCamera();
        statusBar()->showMessage("Camera 1 DisConnected");
    }
    else if(activeCamera=="CAM2"){
        Cam2cilent->disconnectCamera();
        statusBar()->showMessage("Camera 2 Disconnected");
    }
    activeCamera.clear();
}



void MainWindow::on_LearnBtn_clicked()
{
    int goodCount=0;
    int badCount=0;

    for(int row=0; row < ui->tableWidget->rowCount(); ++row){
        QTableWidgetItem *item=ui->tableWidget->item(row,6);
        if(item){
            QString status=item->text().toUpper();
            if(status=="GOOD"){
                goodCount++;
            }
            else if(status=="BAD"){
                badCount++;
            }
        }
    }
    int totalCount=goodCount+badCount;

    // QMessageBox::information(this, "Learn Results",QString("Good Count: %1\nBad Count: %2\nTotal Count: %3").arg(goodCount).arg(badCount).arg(totalCount));

    ui->lineEdit_TotalCount->setText(QString::number(totalCount));
    ui->lineEdit_GoodCount->setText(QString::number(goodCount));
    ui->lineEdit_BadCount->setText(QString::number(badCount));

    if(activeCamera == "CAM1"){
        goodCountCAM1 = goodCount;
        badCountCAM1 = badCount;
    } else if(activeCamera == "CAM2"){
        goodCountCAM2 = goodCount;
        badCountCAM2 = badCount;
    }
}

