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
