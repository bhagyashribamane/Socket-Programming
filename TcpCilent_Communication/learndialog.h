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
        void requestDisconnect();
        void goodCountUpdated(int count);
        void badCountUpdated(int count);

    public slots:
        void IncomingValue(QString value);

    private slots:
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
        DataBase_Manager *dbManager;

        void updateCounters();
        void addToHistory(QString value, bool isMatch);
};

#endif // LEARNDIALOG_H
