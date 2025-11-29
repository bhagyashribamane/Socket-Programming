#ifndef LEARNDIALOG_H
#define LEARNDIALOG_H
#include "database_manager.h"
#include <QDialog>
#include<QTabWidget>
#include <QDateTime>

namespace Ui {
class LearnDialog;
}
class LearnDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit LearnDialog(QWidget *parent = nullptr);
        ~LearnDialog();

        void setDatabaseManager(DataBase_Manager *db);

    signals:
        void learnValueChanged(QString value);
        // used for disconnect button
        void requestDisconnect();

        void goodCountUpdated(int count);
        void badCountUpdated(int count);

        // send data in productname table
         void sendTeachData(QString cameraValue, QString result);

    public slots:
        void IncomingValue(QString value);

    private slots:
        // for teach  , clear , close , disCoonect buttons
        void TeachClicked();
        void ClearClicked();
        void closeClicked();
        void DisConnected();

    private:
        Ui::LearnDialog *ui;
        QString taughtValue;
        int goodCount = 0;
        int badCount = 0;
        int totalCount = 0;

        // DataBase_Manager  class of object
        DataBase_Manager *dbManager;

        // used for good bad , total counters display on screen
        void updateCounters();

        // shows only 10 values on  pages
        void addToHistory(QString value, bool isMatch);
};

#endif // LEARNDIALOG_H
