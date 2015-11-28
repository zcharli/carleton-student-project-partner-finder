#include "cupidsession.h"

CupidSession* CupidSession::singleton = NULL;

CupidSession::CupidSession()
{
    currentUser = NULL;
    currentPPP = NULL;
    currentProject = NULL;
}

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

void CupidSession::setCurrentProject(Project* projectToSet)
{
    currentProject = projectToSet;
}

void CupidSession::deleteCurrentUser()
{
    if(currentUser != NULL)
    {
        delete currentUser;
        currentUser = NULL;
    }
}

void CupidSession::deleteCurrentProject()
{
    if(currentProject != NULL)
    {
        delete currentProject;
        currentProject = NULL;
    }
}

User* CupidSession::getCurrentUser()
{
    return currentUser;
}

Project* CupidSession::getCurrentProject()
{
    return currentProject;
}

CupidSession::~CupidSession()
{
    delete currentUser;
}
