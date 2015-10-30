#include "cupidsession.h"

CupidSession* CupidSession::singleton = NULL;

CupidSession* CupidSession::getInstance()
{
    if(singleton == NULL)
    {
        singleton = new CupidSession();
        return singleton;
    }
    else
    {
        return singleton;
    }
}

void CupidSession::setCurrentUser(User* userToSet)
{
    currentUser = userToSet;
}

void CupidSession::deleteCurrentUser()
{
    delete currentUser;
    currentUser = NULL;
}

User* CupidSession::getCurrentUser()
{
    return currentUser;
}

CupidSession::~CupidSession()
{
  delete currentUser;
}
