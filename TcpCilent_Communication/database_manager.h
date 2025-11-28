#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDateTime>
#include <QObject>

class DataBase_Manager
{
    // Q_OBJECT
public:
    explicit DataBase_Manager(QObject *parent = nullptr);
    bool connectDatabase();


    int insertjob(QString productName , QString taughtValue , QString cameraID , QDate StartTime);
    void updateJob(int jobId, int goodCount , int badCount , QDateTime stopTime);
    // int startSession(const QString &cameraId, const QString &compareValue);
    // void updateCounts(int sessionId, int goodCount, int badCount);
    // void stopSession(int sessionId);

    // void insertRecord(QString taughtValue , QString scannedValue , bool isGood);

private:
    QSqlDatabase db;


};

#endif // DATABASE_MANAGER_H

