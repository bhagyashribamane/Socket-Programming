#include "database_manager.h"
#include <QDebug>
#include<QSqlError>

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

void DataBase_Manager::insertRecord(QString taughtValue, QString scannedValue, bool isGood)
{
    qDebug() << "Inserting into database...";
    QSqlQuery query;
    query.prepare("INSERT INTO cameradata(timestamp, taught_value, scanned_value, result) "
                  "VALUES(NOW(), :taught, :scan, :result)");

    query.bindValue(":taught", taughtValue);
    query.bindValue(":scan", scannedValue);
    query.bindValue(":result", isGood ? "Good" : "Bad");

    if(!query.exec()){
        qDebug() << "Insert Failed:" << query.lastError().text();
    } else {
        qDebug() << "Record Inserted Successfully!";
    }

}
