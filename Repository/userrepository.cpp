#include "userrepository.h"
#include "Models/user.h"
#include "Models/projectpartnerprofile.h"

UserRepository::UserRepository()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "cuPIDdb";
    db.setDatabaseName(dbName);
}

UserRepository::~UserRepository() {}

unsigned int UserRepository::save(const User& userObj)
{
    return 0;
}

unsigned int UserRepository::deleteFromRepo(const int idToDelete)
{
    return 0;
}

User& UserRepository::fetchById(const int idToFetch)
{
    QString i = "";
    QString b = "";
    QString c = "";
    User placeholder(i,b,c,777);
    return placeholder;
}

QVector<User*>& UserRepository::fetchAll(const int idToFetch)
{
    QVector<User*> placeholder;
    return placeholder;
}

bool UserRepository::validateLogin(const QString&)
{
    return true;
}

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
