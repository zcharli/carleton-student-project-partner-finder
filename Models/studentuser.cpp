#include "studentuser.h"
#include "projectpartnerprofile.h"
#include "project.h"

StudentUser::StudentUser(QString& fName, QString& lName, QString& userName, int id):
    User(fName, lName, userName, id)
{
    profile = NULL;
}

StudentUser::~StudentUser()
{
    delete profile;
}

int StudentUser::getNumberOfProjectsRegistered()
{
    return registeredProjects.size();
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

ProjectPartnerProfile& StudentUser::getProfile()
{
    return *profile;
}
