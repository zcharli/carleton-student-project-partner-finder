#include "user.h"

User::User(QString& firstName, QString& lastName, QString& userName, int id)
{
  this->firstName = firstName;
  this->lastName = lastName;
  this->userName = userName;
  this->id = id;
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

void User::setFirstName(QString& newFirstName)
{
  firstName = newFirstName;
}

void User::setLastName(QString& newLastName)
{
  lastName = newLastName;
}

void User::setUserName(QString& newUserName)
{
  userName = newUserName;
}
