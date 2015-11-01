#include "project.h"
#include "projectpartnerprofile.h"
#include "studentuser.h"

Project::Project(QString& title, QString& desc)
{
    this->title = title;
    this->description = desc;
    numberOfRegisteredUsers = 0;

    //initialize configurations array
    projectConfigurations = Configuration::DefaultConfigurations();
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

void Project::changeConfiguration(Configuration config)
{
    projectConfigurations[(int)(config.getType())] = config;
}

void Project::registerPPP(ProjectPartnerProfile* profile)
{
    registeredPPPs.insert(profile);
    profile->getStudentUser().addProjectToRegisteredProjects(this);
}

void Project::unRegisterPPP(ProjectPartnerProfile* profile)
{
    if (isPPPRegistered(profile))
    {
        registeredPPPs.remove(profile);
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

void Project::setProjectId(int id)
{
    this->id = id;
}

int Project::getProjectId()
{
    return id;
}

void Project::addPPPtoProject(ProjectPartnerProfile *ppp)
{
    if(isPPPRegistered(ppp))
    {
        // Shouldnt be adding multiples in a set, this is bad with allocated memeory
        delete ppp;
    }
    else
    {
        registeredPPPs.insert(ppp);
    }
}
