#include "project.h"
#include "projectpartnerprofile.h"
#include "configuration.h"
#include "studentuser.h"

Project::Project(QString& title, QString& desc)
{
    this->title = title;
    this->description = desc;
}

Project::~Project()
{}

//accessor Functions
QVector<Configuration>& Project::getProjectConfigurations()
{
    return projectConfigurations;
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
