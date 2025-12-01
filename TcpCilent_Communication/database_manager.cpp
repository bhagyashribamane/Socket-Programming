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

bool DataBase_Manager::CreateProductTable(QString &ProductName)
{
    QString tableName =ProductName.trimmed().replace(" ","_");


    QSqlQuery checkQuery;
    checkQuery.prepare("SHOW TABLES LIKE :tableName");
    checkQuery.bindValue(":tableName",ProductName);

    bool exists=false;

    if(checkQuery.exec() && checkQuery.next()) {
        exists = true;
        qDebug() << "Table Already Exists";
    }

    if(!exists){
        QString CreateTable=QString(
                                  "CREATE TABLE IF  NOT EXISTS %1("
                                  "id INT PRIMARY KEY AUTO_INCREMENT,"
                                  "CameraValue TEXT,"
                                  "timestamp  DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                  "result TEXT)"
                                  ).arg(tableName);


        QSqlQuery query;
        if(!query.exec(CreateTable)){
            qDebug()<<"Table Creation Failed"<<query.lastError();
            return false;
        }

        return true;
    }
}

bool DataBase_Manager::insertCameraData(const QString &ProductName, const QString &CameraValue, const QString &Result)
{
    QString tableName =ProductName.trimmed().replace(" ","_");

    qDebug() << "Inserting into table:" << tableName << "CameraValue:" << CameraValue << "Result:" << Result;

    QSqlQuery query;
    query.prepare(QString("INSERT INTO `%1` (CameraValue, result, timestamp) VALUES (:value, :result, NOW())").arg(tableName));

    query.bindValue(":value", CameraValue);
    query.bindValue(":result", Result);

    if(!query.exec()) {
        qDebug() << "Insert Record Failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Data Inserted Successfully!";
    return true;
}
