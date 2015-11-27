#include "administratoruser.h"
#include "project.h"

AdministratorUser::AdministratorUser(QString& fName, QString& lName, QString& userName, int id):
    User(fName, lName, userName, id)
{
    userType = Administrator;
}

AdministratorUser::~AdministratorUser()
{

}


bool AdministratorUser::serializeJSONForSave(QJsonObject& userJSON)
{
    if(id != 0)
    {
        userJSON["id"] = id;
    }

    userJSON["firstName"] = firstName;
    userJSON["lastName"] = lastName;
    userJSON["userName"] = userName;
    userJSON["userType"] = (int)userType;

    return true;
}


bool AdministratorUser::deserializeJSONFromRetrieve(const QJsonObject& userJSON)
{
    id = userJSON["id"].toInt();
    firstName = userJSON["firstName"].toString();
    lastName = userJSON["lastName"].toString();
    userName = userJSON["userName"].toString();
    userType = (UserType)userJSON["userType"].toInt();

    return true;
}
