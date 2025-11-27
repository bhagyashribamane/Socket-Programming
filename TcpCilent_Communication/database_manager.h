#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include <QObject>

class DataBase_Manager
{
    // Q_OBJECT
public:
    explicit DataBase_Manager(QObject *parent = nullptr);
    bool connectDatabase();
    void insertRecord(QString taughtValue , QString scannedValue , bool isGood);

private:
    QSqlDatabase db;


};

#endif // DATABASE_MANAGER_H

