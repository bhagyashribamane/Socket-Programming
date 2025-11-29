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

    // insert data in to database
    int insertjob(QString productName , QString taughtValue , QString cameraID , QDate StartTime);
    void updateJob(int jobId, int goodCount , int badCount , QDateTime stopTime);


    // create productname table
    bool CreateProductTable(QString &ProductName);
    bool insertCameraData(const QString &ProductName , const QString &CameraValue , const QString &Result);

private:
    QSqlDatabase db;


};

#endif // DATABASE_MANAGER_H

