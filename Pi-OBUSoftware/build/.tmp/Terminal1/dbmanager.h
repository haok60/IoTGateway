#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDriver>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
class DbManager
{
public:
    DbManager();
    QStringList getdata(int node,QString table);
    bool insertdata(int node, int value, QString table);
    bool deletedata(int node, QString table);
    QStringList getalldata(QString table);
    bool deletealldata(QString table);
    QDateTime time;

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
