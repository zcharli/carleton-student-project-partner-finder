#ifndef PROJECTREPOSITORY_H
#define PROJECTREPOSITORY_H

#include <QVector>
#include <QtSql/QSqlDatabase>

class ProjectRepository
{
public:
  ProjectRepository(QSqlDatabase& db);
  ~ProjectRepository();
private:
    QSqlDatabase db;
};

#endif // PROJECTREPOSITORY_H
