#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "learndialog.h"
#include "database_manager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
// We created TcpClient as a separate class to properly manage all
// TCP communication logic independently from the UI.
class TcpClient;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onBtnConnectCam1();
    void onBbtnConnectCam2();
    // This slot is called whenever new data is received from the camera via TcpClient
    void onDataRecevied(QString ascii , QString hex);
    // This slot is triggered when the user clicks the Connect button in the UI.
    void onConnectedButton();
    // Triggered when the user clicks the Disconnect button.
    void onDisconnectedButton();
    // Triggered when the user clicks the Learn button.
    void onLearnButton();
    // Handles errors emitted from TcpClient
    void onClickError(QString message);
    // Discoonect button from learnDialog
    void handleDisconnect();

signals:
    // newDataAvailable is a communication channel between the main window and other dialogs or widgets.
    // Whenever new camera data arrives, you emit this signal, and any connected slots will get the value.
    void newDataAvailable(const QString &value);

private:
    Ui::MainWindow *ui;
    // Pointer to your TcpClient object, which handles TCP socket communication with the camera.
    TcpClient *Cam1cilent;
    TcpClient *Cam2cilent;


    QDateTime startTime;
    QDateTime stopTime;

    // Database job IDs for cameras
    int jobIdCAM1 = -1;
    int jobIdCAM2 = -1;

    // Good/Bad counters
    int goodCountCAM1 = 0;
    int badCountCAM1 = 0;

    int goodCountCAM2 = 0;
    int badCountCAM2 = 0;

    // is used  to keep track of which camera is currently communicating.
    QString activeCamera;

    // Pointer to the Learn dialog window where users can "teach" a value and track Good/Bad counts.
     LearnDialog *learnDialog;
     DataBase_Manager *dbManager;
};
#endif // MAINWINDOW_H
