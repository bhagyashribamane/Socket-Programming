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
    if(data.length()>=8){
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
 // tcpcilent objects for cameras
    Cam1cilent = new TcpClient(this);
    Cam2cilent=new TcpClient(this);

    // we are creating an instance of the LearnDialog class.
    learnDialog = new LearnDialog(this);

    // learnDialog = new LearnDialog(this);

    dbManager = new DatabaseManager();
    learnDialog->setDatabaseManager(dbManager);


    // data received
    connect(Cam1cilent, &TcpClient::dataReceived, this, &MainWindow::onDataRecevied);
    connect(Cam2cilent, &TcpClient::dataReceived, this, &MainWindow::onDataRecevied);

     // error checking
    connect(Cam1cilent, &TcpClient::errorOccurred, this, &MainWindow::onClickError);
    connect(Cam2cilent, &TcpClient::errorOccurred, this, &MainWindow::onClickError);

    // Disconnected BUtton
    // These lines store GOOD/BAD counts separately for Camera 1 and Camera 2 , Always store count to the correct camera
    connect(learnDialog, &LearnDialog::goodCountUpdatedForDisConnectBtn, this, [&](int count){
        if(activeCamera == "CAM1") goodCountCAM1 = count;
        else if(activeCamera == "CAM2") goodCountCAM2 = count;
    });
    connect(learnDialog, &LearnDialog::badCountUpdatedForDisConnectBtn, this, [&](int count){
        if(activeCamera == "CAM1") badCountCAM1 = count;
        else if(activeCamera == "CAM2") badCountCAM2 = count;
    });

    // Because LearnDialog cannot stop or disconnect the camera by itself. thats why create requestDisconneect signal and create in learndialog
    connect(learnDialog, &LearnDialog::requestDisconnect, this, &MainWindow::handleDisconnect);


// This line connects a signal from MainWindow to a slot in LearnDialog. & Whenever MainWindow gets new data, send that data to LearnDialog
    connect(this, &MainWindow::newDataAvailable, learnDialog, &LearnDialog::IncomingValue);

// This line connects a signal from LearnDialog to a slot in MainWindow. sendtechdata signal Emitted from LearnDialog when the user teaches (learns) a new value
// storeteachvalue function inside MainWindow that receives and stores the taught value.
    connect(learnDialog, &LearnDialog::sendTeachData,this, &MainWindow::storeTeachValue);

// table creating
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels({"Actual Data","Identifier", "length","Parsed Value","HEX","Compare Value","Result","Timestamp"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // QComboBox cameras
    connect(ui->comboBox, &QComboBox::currentTextChanged, this ,&MainWindow::onCameraChanged);
    connect(ui->CameraStartBtn,&QPushButton::clicked, this , &MainWindow::onStartCameras);
    connect(ui->CameraStopBtn,&QPushButton::clicked, this , &MainWindow::onStopCameras);

    // learn button
    connect(ui->LearnBtn, &QPushButton::clicked, this , &MainWindow::on_LearnBtn_clicked);
    // show result
    connect(ui->btn_ShowResult, &QPushButton::clicked, this, &MainWindow::onShowResultButton);
    // clear button
    connect(ui->ClearBtn , &QPushButton::clicked, this , &MainWindow::on_ClearBtn_clicked);

// signals for emiit the good , abd , and total counter to the learndialog
    connect(this, &MainWindow::Signal_GoodCountUpdated, learnDialog , [&](int count){
        learnDialog->updateGoodCounter(count);
    });
    connect(this, &MainWindow::signal_BadCountUpdated, learnDialog , [&](int count){
        learnDialog->updateBadCounter(count);
    });
    connect(this, &MainWindow::signal_TotalCountUpdated, learnDialog , [&](int count){
        learnDialog->updateTotalCounter(count);
    });

// qDebug() << "Available SQL Drivers:" << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}
 // This function is called whenever new data is received from the camera.
void MainWindow::onDataRecevied(QString ascii, QString hex)
{
    // The raw data from the camera is in ASCII format, e.g., "RD00041234".parsePacket() extracts parts of the data:packet now holds these structured pieces of data.
    ParsedPacket packet = parsePacket(ascii);
    updateTableWithPacket(packet, ascii, hex);

    // Because your MainWindow receives camera data first, but your LearnDialog also needs that same data.
    emit newDataAvailable(ascii);
}

void MainWindow::updateTableWithPacket(const ParsedPacket &packet, const QString &ascii, const QString &hex)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // always fill the standard columns
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ascii));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(packet.command));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(packet.length)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(packet.value));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(hex));
    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(time));


    // -------- Compare Logic --------
    QString CompareValue = taughtValue;    // local variable, holds the taught value
    QString CompareResult="";                  // local variable, will be GOOD/BAD

    if (learningActive  && !CompareValue.isEmpty())
    {
        if (packet.value == CompareValue)
        {
            CompareResult = "GOOD";
            goodCount++;
        }
        else
        {
            CompareResult = "BAD";
            badCount++;
        }

        totalCount = goodCount + badCount;

        // Update counters in UI
        ui->lineEdit_GoodCount->setText(QString::number(goodCount));
        ui->lineEdit_BadCount->setText(QString::number(badCount));
        ui->lineEdit_TotalCount->setText(QString::number(totalCount));

        emit Signal_GoodCountUpdated(goodCount);
        emit signal_BadCountUpdated(badCount);
        emit signal_TotalCountUpdated(totalCount);
    }

    // Fill Compare Value & Result columns in table
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(CompareValue));  // Compare Value
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(CompareResult)); // Result


    ui->tableWidget->scrollToBottom();

    dbManager->insertProductData(
        ui->lineEditProductName->text().trimmed(),
        packet.value,
        CompareResult,
        QDateTime::currentDateTime()
        );

}
// this function used for show result button
void MainWindow::onShowResultButton()
{
    learnDialog->show();
}
// to show errors
void MainWindow::onClickError(QString message)
{
  statusBar()->showMessage(message, 5000);
}
// from LearnDialog; Disconnect Button when click the data will store bad count ,good count
void MainWindow::handleDisconnect()
{
    if (activeCamera.isEmpty()) {
        QMessageBox::warning(this, "Error", "No active camera");
        return;
    }

    stopTime = QDateTime::currentDateTime();

    if (!dbManager->UpdateJob(activeCamera, stopTime, goodCount, badCount)) {
        QMessageBox::critical(this, "DB Error", "Failed to save job");
        return;
    }

    if (activeCamera == "CAM1" && Cam1cilent)
        Cam1cilent->disconnectCamera();
    else if (activeCamera == "CAM2" && Cam2cilent)
        Cam2cilent->disconnectCamera();

    activeCamera.clear();

    QMessageBox::information(this, "Saved", "Job stored successfully");

}

void MainWindow::storeTeachValue(QString cameraValue, QString result)
{
    if (activeCamera.isEmpty()) {
        QMessageBox::warning(this, "Error", "No active camera");
        return;
    }

    QString productName = ui->lineEditProductName->text().trimmed();
    if (productName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Product name is missing");
        return;
    }

    // Save taught value for currently running job
    if (!dbManager->UpdateTaughtValue(activeCamera, cameraValue)) {
        QMessageBox::critical(this, "DB Error", "Failed to save taught value");
        return;
    }

    qDebug() << "Teach value stored:"
             << "Camera:" << activeCamera
             << "Value:" << cameraValue
             << "Result:" << result;
}
// for camera selection from  combobox
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
        Cam1cilent->disconnectCamera();
    }
    statusBar()->showMessage("camera 2 Selected");
}
}

// for start the camera
void MainWindow::onStartCameras()
{
    QString product = ui->lineEditProductName->text();
    QString ip = ui->lineEditIP->text();
    int port = ui->lineEditPort->text().toInt();

    QDateTime startTime = QDateTime::currentDateTime();

    if (selectedCamera == "Camera 1") {
        activeCamera = "CAM1";

        if (!dbManager->insertJob(activeCamera, product, startTime)) {
            QMessageBox::critical(this, "DB Error", "Job creation failed");
            return;
        }

        Cam1cilent->connectToCamera(ip, port);
    }
    else if (selectedCamera == "Camera 2") {
        activeCamera = "CAM2";

        if (!dbManager->insertJob(activeCamera, product, startTime)) {
            QMessageBox::critical(this, "DB Error", "Job creation failed");
            return;
        }

        Cam2cilent->connectToCamera(ip, port);
    }
}

void MainWindow::onStopCameras()
{
    stopTime = QDateTime::currentDateTime();

    if (activeCamera == "CAM1") {
        Cam1cilent->disconnectCamera();
        statusBar()->showMessage("Camera 1 Disconnected");
    }
    else if (activeCamera == "CAM2") {
        Cam2cilent->disconnectCamera();
        statusBar()->showMessage("Camera 2 Disconnected");
    }

    activeCamera.clear();
}
void MainWindow::on_LearnBtn_clicked()
{
    if (activeCamera.isEmpty()) {
        QMessageBox::warning(this, "Error", "Start camera first");
        return;
    }

    int lastRow = ui->tableWidget->rowCount() - 1;
    if (lastRow < 0) return;

    taughtValue = ui->tableWidget->item(lastRow, 3)->text();
    if (taughtValue.isEmpty()) return;
    learningActive = true;
    goodCount = badCount = totalCount = 0;
    ui->lineEditTaughtVAlue->setText(taughtValue);


    if (!dbManager->UpdateTaughtValue(activeCamera, taughtValue)) {
        QMessageBox::critical(this, "DB Error", "Failed to save taught value");
        return;
    }



}


void MainWindow::on_ClearBtn_clicked()
{
    if(QMessageBox::question(this, "Confirm","Do you want to clear all table data and reset counters?") == QMessageBox::No)
        return;
    //Clear table
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    //Reset counters and flags
    goodCount = 0;
    badCount = 0;
    totalCount = 0;
    learningActive = false;

    //Clear UI fields
    ui->lineEdit_GoodCount->clear();
    ui->lineEdit_BadCount->clear();
    ui->lineEdit_TotalCount->clear();
    ui->lineEditTaughtVAlue->clear();

    statusBar()->showMessage("All data cleared successfully.");

}

