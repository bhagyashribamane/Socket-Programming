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

// It defines a data structure to store a
// parsed version of the raw data received from the camera.When the camera sends data like RD00041234
struct ParsedPacket{
    QString command;
    int length;
    QString value;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    // cameras connection button
    // void onBtnConnectCam1();
    // void onBbtnConnectCam2();

    void updateTableWithPacket(const ParsedPacket &packet, const QString &ascii, const QString &hex);
    // This slot is called whenever new data is received from the camera via TcpClient
    void onDataRecevied(QString ascii , QString hex);


    // Triggered when the user clicks the Learn button.
    void onShowResultButton();
    // Handles errors emitted from TcpClient
    void onClickError(QString message);
    // Discoonect button from learnDialog
    void handleDisconnect();
    void storeTeachValue(QString cameraValue, QString result);
// for combobox cameras
    void onCameraChanged(const QString &camera);
    void onStartCameras();
    void onStopCameras();

signals:
    // newDataAvailable is a communication channel between the main window and other dialogs or widgets.
    // Whenever new camera data arrives, you emit this signal, and any connected slots will get the value.
    void newDataAvailable(const QString &value);

private slots:
    void on_LearnBtn_clicked();

    void on_ClearBtn_clicked();

private:
    Ui::MainWindow *ui;
    // for combobox camera selecttion
    QString selectedCamera;

    // Pointer to your TcpClient object, which handles TCP socket communication with the cameras.
    TcpClient *Cam1cilent;
    TcpClient *Cam2cilent;

// starttime and stoptime for database
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
    bool learningActive = false;
     QString taughtValue;
    int goodCount = 0;
    int badCount = 0;
    int totalCount = 0;

    // Pointer to the Learn dialog window where users can "teach" a value and track Good/Bad counts.
     LearnDialog *learnDialog;
     DataBase_Manager *dbManager;
};
#endif // MAINWINDOW_H
