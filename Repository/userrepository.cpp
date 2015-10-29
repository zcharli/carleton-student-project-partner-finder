#include "userrepository.h"
#include "Models/user.h"
#include "Models/projectpartnerprofile.h"

UserRepository::UserRepository(QSqlDatabase& db)
{
  this->db = db;
}

UserRepository::~UserRepository() {}

int UserRepository::userCreatedPPP(User &user, ProjectPartnerProfile& ppp)
{
    //TODO:
    return 0;
}

int UserRepository::fetchPPPForUser(User &user, ProjectPartnerProfile& ppp)
{
    //TODO:
    return 0;
}

int UserRepository::userUpdatedPPP(User &user, ProjectPartnerProfile &ppp)
{
    //TODO:
    return 0;
}

int UserRepository::userDeletedPPP(User &user, ProjectPartnerProfile &ppp)
{
    //TODO:
    return 0;
}

int UserRepository::retrieveUserWithUsername(QString& username, User& user)
{
  //TODO:
  return 0;
}

int UserRepository::createUser(User& user)
{
  //TODO:
  return 0;
}
