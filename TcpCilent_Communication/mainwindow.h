#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "learndialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TcpClient;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onDataRecevied(QString ascii , QString hex);
    void onConnectedButton();
    void onDisconnectedButton();
    void onLearnButton();

    void onClickError(QString message);

signals:
    void newDataAvailable(const QString &value);



private:
    Ui::MainWindow *ui;
    TcpClient *cilent;
     LearnDialog *learnDialog;
};
#endif // MAINWINDOW_H
