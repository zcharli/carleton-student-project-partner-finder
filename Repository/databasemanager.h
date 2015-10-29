#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    /*!
     *       @param: none
     *        @desc: gets the error of the last sql statement
     *      @return: SqlError
     */
    QSqlError lastError();

    /*!
     *       @param: none
     *        @desc: gets the opened database
     *      @return: QSqlDatabase
     */
    QSqlDatabase& getDB();

private:
    QSqlDatabase db;

};

#endif // DATABASEMANAGER_H
