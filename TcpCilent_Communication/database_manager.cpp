#include "database_manager.h"
#include <QDebug>
#include<QSqlError>
#include<QSqlQuery>

DataBase_Manager::DataBase_Manager(QObject *parent){}

bool DataBase_Manager::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("learn_system");
    db.setUserName("root");
    db.setPassword("Pwtech@7227");

    db.setConnectOptions("MYSQL_OPT_SSL_MODE=DISABLED;");

    if (db.open()) {
        qDebug() << "Database Connected Successfully!";
        return true;
    } else {
        qDebug() << "Database NOT Connected: " << db.lastError().text();
        return false;
    }
}

int DataBase_Manager::insertjob(QString ProductName, QString taughtValue, QString cameraID, QDate StartTime)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QSqlQuery query;
       query.prepare("INSERT INTO jobdetails(ProductName, CameraId,StartTime,TaughtValue) "
                  "VALUES(:product, :camera, :start, :taught)");

    query.bindValue(":product", ProductName);
    query.bindValue(":camera", cameraID);
    query.bindValue(":start", timestamp);
    query.bindValue(":taught", taughtValue);


    if(query.exec()) {
        return query.lastInsertId().toInt();
    } else {
        qDebug() << "Insert Job Failed:" << query.lastError().text();
        return -1;
    }
}

void DataBase_Manager::updateJob(int jobId, int goodCount, int badCount, QDateTime stopTime)
{
    QSqlQuery query;
    query.prepare("UPDATE jobdetails SET Stoptime=:stop, GoodCount=:good, BadCount=:bad "
                  "WHERE id=:id");
    query.bindValue(":stop", stopTime.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":good", goodCount);
    query.bindValue(":bad", badCount);
    query.bindValue(":id", jobId);

    if(!query.exec()) {
        qDebug() << "Update Job Failed:" << query.lastError().text();
    } else {
        qDebug() << "Job Updated Successfully";
    }
}

