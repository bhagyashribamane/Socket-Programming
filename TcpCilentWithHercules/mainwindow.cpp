#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpcilents.h"

TcpCilents *cilent;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cilent = new TcpCilents(this);
    connect(cilent , &TcpCilents::dataReceived, this, [=](QString ascii, QString hex){
        ui->textEdit_hex->append(hex);
        ui->textEdit_ascii->append(ascii);
    });

    cilent->connectToCamera("192.168.5.250", 23);
}

MainWindow::~MainWindow()
{
    delete ui;
}
