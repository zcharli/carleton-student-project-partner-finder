#include "studentuser.h"
#include "projectpartnerprofile.h"
#include "project.h"

StudentUser::StudentUser(QString& fName, QString& lName, QString& userName, int id):
    User(fName, lName, userName, id)
{
    profile = NULL;
    userType = Student;
    pppIDForFetch = 0;
}

StudentUser::~StudentUser()
{
    delete profile;
}

int StudentUser::getNumberOfProjectsRegistered()
{
    return numProjectsRegistered;
}

void StudentUser::setNumberOfProjectsRegistered(int newNum)
{
    numProjectsRegistered = newNum;
}

void StudentUser::setFetchIDForPPP(int fetchID)
{
    pppIDForFetch = fetchID;
}

int StudentUser::getFetchIDForPPP()
{
    return pppIDForFetch;
}

void StudentUser::addProjectToRegisteredProjects(Project* project)
{
  registeredProjects.append(project);
}

void StudentUser::removeProjectFromRegisteredProjects(Project* project)
{
  int index = registeredProjects.indexOf(project);

  if (index != -1)
  {
      registeredProjects.remove(index);
  }
}

bool StudentUser::isRegisteredInProject(Project* project)
{
    return registeredProjects.contains(project);
}

ProjectPartnerProfile* StudentUser::getProfile()
{
    if(profile == NULL)
    {
        return NULL;
    }
    return profile;
}
