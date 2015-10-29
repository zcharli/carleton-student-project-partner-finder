#include "cupidsession.h"

User* CupidSession::currentUser = 0;
bool CupidSession::isInstance = false;
CupidSession* CupidSession::singleton = NULL;

CupidSession* CupidSession::getInstance()
{
    if(!isInstance)
    {
        singleton = new CupidSession();
        isInstance = true;
        return singleton;
    }
    else
    {
        return singleton;
    }
}

CupidSession::~CupidSession()
{
  isInstance = false; 
  delete currentUser;
}
