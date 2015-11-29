#include "administratoruser.h"
#include "project.h"
#include "mapconfigs.h"

AdministratorUser::AdministratorUser(QString& fName, QString& lName, QString& userName):
    User(fName, lName, userName)
{
    userType = Administrator;
}

AdministratorUser::AdministratorUser(const QJsonObject& adminJSON)
{
    deserializeJSONFromRetrieve(adminJSON);
}

AdministratorUser::~AdministratorUser()
{}


bool AdministratorUser::serializeJSONForSave(QJsonObject& userJSON)
{
    if(id != 0)
    {
        userJSON[USER_id] = id;
    }

    userJSON[USER_firstName] = firstName;
    userJSON[USER_lastName] = lastName;
    userJSON[USER_userName] = userName;
    userJSON[USER_userType] = (int)userType;

    return true;
}


bool AdministratorUser::deserializeJSONFromRetrieve(const QJsonObject& userJSON)
{
    id = userJSON[USER_id].toInt();
    firstName = userJSON[USER_firstName].toString();
    lastName = userJSON[USER_lastName].toString();
    userName = userJSON[USER_userName].toString();
    userType = (UserType)userJSON[USER_userType].toInt();

    return true;
}
