#include "dbmanager.h"
DbManager::DbManager()
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName("./WSAN/gateway.db");

       if (!m_db.open())
       {
          qDebug() << "Error: connection with database fail";
       }
       else
       {
          qDebug() << "Database: connection ok";

       }
}
bool DbManager::insertdata(int node, int value, QString table)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO "+table+"(timerc,Node,value) VALUES (:date,:node,:value)");
    query.bindValue(":date", time.currentDateTimeUtc());
    query.bindValue(":node",node);
    query.bindValue(":value",value);
    if(query.exec())
       {
           success = true;
       }
    return success;

}

QStringList DbManager::getdata(int node, QString table)
{
    QStringList list;
    QSqlQuery query;
    QString queryString = "SELECT * FROM "+table+" WHERE Node = "+QString::number(node);
    qDebug()<<queryString;
    query.exec(queryString);
    while (query.next()) {
        QSqlRecord record = query.record();
        QString time = record.value(0).toString();
        list.append(time);
        QString Value = QString::number(record.value(2).toDouble());
        list.append(Value);
        qDebug() << "Time : "<<record.value(2).toDouble();
    }
    return list;
}

bool DbManager::deletedata(int node, QString table)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("DELETE FROM "+table+" WHERE Node = :node");
    query.bindValue(":node",node);
    query.exec();
    if(query.exec())
       {
           success = true;
       }
    return success;
}
bool DbManager::deletealldata(QString table)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("DELETE FROM "+table);
    query.exec();
    if(query.exec())
       {
           success = true;
       }
    return success;
}

