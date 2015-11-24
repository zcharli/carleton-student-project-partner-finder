#include "databasemanager.h"
#include "QDebug"
#include "QDir"
#include <QtSql>
//#include "QSqlQuery"
//#include "QSqlQueryModel"

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //QString path = QDir::currentPath();
    //path.append("/../cuPID/Data/cuPIDdb");
    //QString dbPath = "/cuPID/Data/cuPIDdb";
    //QString dbPath = "/home/student/cuPIDdb";
    QString dbPath = "Data/cuPIDdb";
    db.setDatabaseName("../cuPID/"+dbPath);
    db.open();
    if(db.isOpen())
    {
        qDebug() << "Database is opened for business";
    }
    else
    {
        qDebug() << db.lastError();
    }
}

DatabaseManager::~DatabaseManager()
{
}

QSqlDatabase& DatabaseManager::getDB()
{
    return db;
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}
