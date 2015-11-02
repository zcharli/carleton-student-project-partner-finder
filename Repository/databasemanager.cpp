#include "databasemanager.h"
#include "QDebug"
#include "QDir"
//#include "QSqlQuery"
//#include "QSqlQueryModel"

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //QString dbPath = QDir::currentPath() + "/Data/cuPIDdb";
    QString dbPath = "/home/admin/cuPIDdb";
    db.setDatabaseName(dbPath);
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

DatabaseManager::~DatabaseManager() {}

QSqlDatabase& DatabaseManager::getDB()
{
    return db;
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}
