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
    return myProjects.size();
}

void AdministratorUser::addProjectToCreatedProjects(Project* project)
{
    myProjects.append(project);
}


void AdministratorUser::removeProjectFromCreatedProjects(Project* project)
{
    int index = myProjects.indexOf(project);

    if (index != -1)
    {
        myProjects.remove(index);
    }
}

bool AdministratorUser::didCreateProject(Project* project)
{
    return containsProject(project);
}
