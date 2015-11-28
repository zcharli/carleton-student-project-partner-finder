#include "projectrepository.h"

ProjectRepository::ProjectRepository(QSqlDatabase& db)
{
    this->db = db;
}

ProjectRepository::~ProjectRepository()
{}
