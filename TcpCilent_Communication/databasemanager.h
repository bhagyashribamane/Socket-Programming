#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include<QString>
#include<QObject>
#include<QSqlDatabase>
#include<QDateTime>
#include<QSqlQuery>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    bool openDatabase();

    int insertJob(QString CameraId, QString ProductName ,QDateTime StartTime);
    bool UpdateJob(const QString &CameraId, QDateTime &StopTime, int GoodCount , int BadCount);

    bool CreateProductTable(QString ProductName);

    bool insertProductData(QString ProductName, QString CameraValue, QString Result , QDateTime Time);
    bool UpdateTaughtValue( QString CameraId,const QString &TaughtValue);

private:
    QSqlDatabase dbManager;




};

#endif // DATABASEMANAGER_H
