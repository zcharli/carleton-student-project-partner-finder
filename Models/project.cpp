#include "project.h"
#include "projectpartnerprofile.h"
#include "studentuser.h"

Project::Project(QString& title, QString& desc)
{
    this->title = title;
    this->description = desc;
    numberOfRegisteredUsers = 0;

    //initialize configurations array
    projectConfigurations = Configurations::DefaultConfigrations();
}

Project::~Project()
{
    delete[] projectConfigurations;
    projectConfigurations = NULL;
}

//accessor Functions

Configuration Project::getProjectConfiguration(int index)
{
    //TODO: Bounds checking
    return projectConfigurations[index];
}

void Project::changeConfiguration(Configuration newConfiguration)
{
    projectConfigurations[newConfiguration.getType()] = newConfiguration;
}

void Project::registerPPP(ProjectPartnerProfile* profile)
{
    registeredPPPs.append(profile);
    profile->getStudentUser().addProjectToRegisteredProjects(this);
}

void Project::unRegisterPPP(ProjectPartnerProfile* profile)
{
    int index = registeredPPPs.indexOf(profile);

    if (index != -1)
    {
        registeredPPPs.remove(index);
        profile->getStudentUser().removeProjectFromRegisteredProjects(this);
    }
}

int Project::getNumberOfRegisteredUsers()
{
    return numberOfRegisteredUsers;
}

void Project::setNumberOfRegisteredUsers(int newNum)
{
    numberOfRegisteredUsers = newNum;
}

bool Project::isPPPRegistered(ProjectPartnerProfile* profile)
{
    return registeredPPPs.contains(profile);
}

QString& Project::getTitle()
{
    return title;
}

QString& Project::getDescription()
{
    return description;
}

void Project::setTitle(QString& newTitle)
{
    title = newTitle;
}

void Project::setDescription(QString& newDescription)
{
    description = newDescription;
}
