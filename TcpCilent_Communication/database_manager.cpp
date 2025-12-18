#include "database_manager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include<QMessageBox>

DataBase_Manager::DataBase_Manager(QObject *parent){}

// Connect to database
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

// Insert a new job
int DataBase_Manager::insertjob(QString ProductName, QString taughtValue, QString cameraID,  QDateTime Starttime)
{
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return -1;
    }

    QSqlQuery query;
    query.prepare(R"(INSERT INTO jobdetails(ProductName, CameraId, StartTime, TaughtValue, GoodCount, BadCount)
                     VALUES(:product, :camera, :start, :taught, 0, 0))");
    query.bindValue(":product", ProductName);
    query.bindValue(":camera", cameraID);
    query.bindValue(":start", Starttime.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":taught", taughtValue);

    if(query.exec()) {
        qDebug() << "Job Inserted Successfully!";
        return query.lastInsertId().toInt();
    } else {
        qDebug() << "Insert Job Failed:" << query.lastError().text();
        return -1;
    }
}

// Update job counts and stop time
void DataBase_Manager::updateJob(int jobId, int goodCount, int badCount, QDateTime stopTime)
{
    if (!db.isOpen()) return;

    QSqlQuery query;
    query.prepare(R"(UPDATE jobdetails
                     SET StopTime=:stop, GoodCount=:good, BadCount=:bad
                     WHERE id=:id)");
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

// Create product-specific table
 bool DataBase_Manager::CreateProductTable(QString &ProductName)
{
    QString tableName = ProductName.trimmed().replace(" ", "_");

    QSqlQuery checkQuery;
    checkQuery.prepare("SHOW TABLES LIKE :tableName");
    checkQuery.bindValue(":tableName", tableName);

    bool exists = false;
    if (checkQuery.exec() && checkQuery.next()) {
        exists = true;
        qDebug() << "Table already exists:" << tableName;

    }

    if (!exists) {
        QString createTable = QString(
                                  "CREATE TABLE IF NOT EXISTS `%1` ("
                                  "id INT PRIMARY KEY AUTO_INCREMENT,"
                                  "CameraValue TEXT,"
                                  "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                  "result TEXT)").arg(tableName);

        QSqlQuery query;
        if (!query.exec(createTable)) {
            qDebug() << "Table Creation Failed:" << query.lastError();
            return false;
        }
        qDebug() << "Table Created Successfully:" << tableName;
    }

    return true;
}

bool DataBase_Manager::insertCameraData(const QString &ProductName,const QString &CameraValue,const QString &TaughtValue,int jobId)
{
    if (!db.isOpen()) return false;

    QString tableName = ProductName.trimmed().replace(" ", "_");
    CreateProductTable(tableName);

    QString result = (CameraValue == TaughtValue) ? "Good" : "Bad";

    //Insert camera reading
    QSqlQuery query;
    query.prepare(QString("INSERT INTO `%1` (CameraValue, result, timestamp) "
                          "VALUES (:value, :result, NOW())").arg(tableName));
    query.bindValue(":value", CameraValue);
    query.bindValue(":result", result);
    query.exec();

    //Update jobdetails counts
    QSqlQuery countUpdate;
    countUpdate.prepare("UPDATE jobdetails SET "
                        "GoodCount = GoodCount + :good, "
                        "BadCount  = BadCount  + :bad "
                        "WHERE id = :id");

    countUpdate.bindValue(":good", (result == "Good") ? 1 : 0);
    countUpdate.bindValue(":bad",  (result == "Bad")  ? 1 : 0);
    countUpdate.bindValue(":id", jobId);
    countUpdate.exec();

    return true;
}

