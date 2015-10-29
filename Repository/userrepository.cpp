#include "userrepository.h"
#include "Models/user.h"
UserRepository::UserRepository() {}

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

bool validateLogin(const QString&)
{
    return true;
}
