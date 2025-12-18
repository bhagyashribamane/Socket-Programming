#include "databasemanager.h"
#include<QSqlError>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    openDatabase();
}


bool DatabaseManager::openDatabase()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        dbManager = QSqlDatabase::database("qt_sql_default_connection");
        return dbManager.isOpen();
    }
    dbManager=QSqlDatabase::addDatabase("QMYSQL");
    dbManager.setHostName("localhost");
    dbManager.setDatabaseName("Camera_Inspection");
    dbManager.setUserName("root");
    dbManager.setPassword("Pwtech@7227");
    dbManager.setConnectOptions("MYSQL_OPT_SSL_MODE=DISABLED;");

    if (dbManager.open()) {
        qDebug() << "Database Connected Successfully!";
        return true;
    } else {
        qDebug() << "Database NOT Connected: " << dbManager.lastError().text();
        return false;
    }

}

int DatabaseManager::insertJob(QString CameraId, QString ProductName,QDateTime StartTime)
{

    QSqlQuery query(dbManager);
    query.prepare(
        "INSERT INTO jobdetails "
        "(CameraId, ProductName, StartTime, TaughtValue) "
        "VALUES (:CameraId, :ProductName, :StartTime, :TaughtValue)"
        );

    query.bindValue(":CameraId", CameraId);
    query.bindValue(":ProductName", ProductName);
    query.bindValue(":StartTime", StartTime);
    query.bindValue(":TaughtValue", "");

    if (!query.exec()) {
        qDebug() << "Insert job failed:" << query.lastError();
        return -1;
    }

    return query.lastInsertId().toInt();
}

bool DatabaseManager::UpdateJob(const QString &CameraId, QDateTime &StopTime, int GoodCount, int BadCount)
{
    QSqlQuery query(dbManager);
    query.prepare(
        "UPDATE jobdetails "
        "SET StopTime =:StopTime,"
        "GoodCount = :GoodCount,"
        "BadCount = :BadCount,"
        "CameraId=:CameraId"

        );
    query.addBindValue(StopTime);
    query.addBindValue(GoodCount);
    query.addBindValue(BadCount);
    query.addBindValue(CameraId);

    if (!query.exec()) {
        qDebug() << "Update Job failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::CreateProductTable(QString ProductName)
{
    QString tableName = ProductName.trimmed().replace(" ", "_");

    QSqlQuery checkQuery;
    checkQuery.prepare("SHOW TABLES LIKE :tableName");
    checkQuery.bindValue(":tableName", tableName);

    bool exists = false;

    if (checkQuery.exec() && checkQuery.next()) {
        exists = true;
        // qDebug() << "Table already exists:" << tableName;
    }

    if (!exists) {
        QString CreateTable = QString(
                                  "CREATE TABLE IF NOT EXISTS `%1` ("
                                  "id INT PRIMARY KEY AUTO_INCREMENT,"
                                  "CameraValue TEXT,"
                                  "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                  "result TEXT)").arg(tableName);

        QSqlQuery query;
        if (!query.exec(CreateTable)) {
            qDebug() << "Table Creation Failed:" << query.lastError();
            return false;
        }

        qDebug() << "Table Created Successfully:" << tableName;
    }

    return true;

}

bool DatabaseManager::insertProductData(QString ProductName, QString CameraValue, QString Result, QDateTime Time)
{
    if (!dbManager.isOpen())
    {
        qDebug() << "Database not open!";
        return false;
    }

    QString tableName =ProductName.trimmed().replace(" ","_");


    QString tempName = tableName;
    CreateProductTable(tempName);
    // qDebug() << "Inserting into table:" << tableName << "CameraValue:" << CameraValue << "Result:" << Result;

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

bool DatabaseManager::UpdateTaughtValue(QString CameraId, const QString &TaughtValue){
    QSqlQuery query;
    query.prepare(
        "UPDATE jobdetails "
        "SET TaughtValue = :TaughtValue , "
        "CameraId = :CameraId"
        );

    query.bindValue(":TaughtValue",TaughtValue);
    query.bindValue(":CameraId", CameraId);

    if(!query.exec()){
        qDebug() << "Update taught value failed" << query.lastError();
        return false;
    }
    return true;
}
