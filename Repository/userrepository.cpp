#include "userrepository.h"

UserRepository::UserRepository(QSqlDatabase& db)
{
  this->db = db;
}

UserRepository::~UserRepository() {}
