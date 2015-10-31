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

void CupidSession::setCurrentProfile(ProjectPartnerProfile* profileToSet)
{
    currentPPP = profileToSet;
}

void CupidSession::deleteCurrentUser()
{
    if(currentUser)
    {
        delete currentUser;
        currentUser = NULL;
    }
}

void CupidSession::deleteCurrentProject()
{
    if(currentProject)
    {
        delete currentProject;
        currentProject = NULL;
    }
}

void CupidSession::deleteCurrentProfile()
{
    if(currentPPP)
    {
        delete currentPPP;
        currentPPP = NULL;
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

ProjectPartnerProfile* CupidSession::getCurrentProfile()
{
    return currentPPP;
}

CupidSession::~CupidSession()
{
  delete currentUser;
}
