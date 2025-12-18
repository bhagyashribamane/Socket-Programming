#ifndef LEARNDIALOG_H
#define LEARNDIALOG_H
#include "DatabaseManager.h"
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

        void setDatabaseManager(DatabaseManager *db);

    signals:
        void learnValueChanged(QString value);
        // used for disconnect button
        void requestDisconnect();
        void goodCountUpdatedForDisConnectBtn(int count);
        void badCountUpdatedForDisConnectBtn(int count);

        // send data in productname table
         void sendTeachData(QString cameraValue, QString result);

    public slots:
        void IncomingValue(QString value);
        // for good bad and total counter
        void updateGoodCounter(int count);
        void updateBadCounter(int count);
        void updateTotalCounter(int count);

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
        // DatabaseManager  class of object
        DatabaseManager *dbManager;

        // shows only 10 values on  pages
        void addToHistory(QString value, bool isMatch);
};

#endif // LEARNDIALOG_H
