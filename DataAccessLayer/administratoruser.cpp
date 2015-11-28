#include "administratoruser.h"
#include "project.h"

AdministratorUser::AdministratorUser(QString& fName, QString& lName, QString& userName):
    User(fName, lName, userName)
{
    userType = Administrator;
}

AdministratorUser::~AdministratorUser()
{

}
