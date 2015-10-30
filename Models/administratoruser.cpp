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

int AdministratorUser::getNumberOfProjectsCreated()
{
    return projectsCreated.size();
}

void AdministratorUser::addProjectToCreatedProjects(Project* project)
{
    projectsCreated.append(project);
}


void AdministratorUser::removeProjectFromCreatedProjects(Project* project)
{
    int index = projectsCreated.indexOf(project);

    if (index != -1)
    {
        projectsCreated.remove(index);
    }
}

bool AdministratorUser::didCreateProject(Project* project)
{
    return projectsCreated.contains(project);
}
