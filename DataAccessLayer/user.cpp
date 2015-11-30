#include "user.h"

User::User(QString firstName, QString lastName, QString userName)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->userName = userName;
    this->id = 0;
}

User::User()
{

  this->firstName = "";
  this->lastName = "";
  this->userName = "";
  this->id = 0;
}

User::~User()
{

}

QString& User::getFirstName()
{
    return firstName;
}

QString& User::getLastName()
{
    return lastName;
}

QString& User::getUserName()
{
    return userName;
}

void User::setFirstName(QString newFirstName)
{
    firstName = newFirstName;
}

void User::setLastName(QString newLastName)
{
    lastName = newLastName;
}

void User::setUserName(QString newUserName)
{
    userName = newUserName;
}

void User::setUserId(int newID)
{
    id = newID;
}

int User::getUserId()
{
    return id;
}

UserType User::getUserType()
{
    return userType;
}

void User::setUserType(UserType t)
{
    userType = t;
}

int User::getNumberOfProjectsAssociated()
{
    return myProjects.size();
}

void User::addProjectToUser(int projectID)
{
    myProjects.insert(projectID);
}


void User::removeProjectFromUser(int projectID)
{
    if(myProjects.contains(projectID))
        myProjects.remove(projectID);
}

QSet<int>& User::getProjectsAssociated(){
    return myProjects;
}

bool User::containsProject(Project& project)
{
    return myProjects.contains(project.getProjectId());
}
