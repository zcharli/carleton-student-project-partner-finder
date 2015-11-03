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

void Project::registerPPP(ProjectPartnerProfile& profile)
{
    //Database updates the numberOfRegistered Users so dont worry about it here
    registeredPPPs.insert(profile.getPPPID());
    profile.getStudentUser().addProjectToUser(this->id);
}

void Project::unRegisterPPP(ProjectPartnerProfile& profile)
{
    //Database updates the numberOfRegistered Users so dont worry about it here
    registeredPPPs.remove(profile.getPPPID());
    profile.getStudentUser().removeProjectFromUser(this->id);
}

int Project::getNumberOfRegisteredUsers()
{
    return numberOfRegisteredUsers;
}

void Project::setNumberOfRegisteredUsers(int newNum)
{
    //Only mostly called by the database
    numberOfRegisteredUsers = newNum;
}

bool Project::isPPPRegistered(ProjectPartnerProfile& profile)
{
    return registeredPPPs.contains(profile.getPPPID());
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

void Project::addPPPtoProject(ProjectPartnerProfile* ppp)
{

}
