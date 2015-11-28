#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QVector>
#include <QtSql/QSqlDatabase>

class UserRepository
{
public:
    UserRepository(QSqlDatabase&);
    ~UserRepository();

private:
    QSqlDatabase db;

};

#endif // USERREPOSITORY_H
