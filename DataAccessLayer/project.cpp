#include "project.h"
#include "projectpartnerprofile.h"
#include "studentuser.h"
#include <QJsonArray>

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
    delete projectConfigurations;
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
    registeredPPPs.insert(profile);
    profile.getStudentUser().addProjectToUser(this->id);
}

void Project::unRegisterPPP(ProjectPartnerProfile& profile)
{
    //Database updates the numberOfRegistered Users so dont worry about it here
    registeredPPPs.remove(profile);
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

void Project::addPPPtoProject(ProjectPartnerProfile*)
{

}

bool Project::serializeJSONForSave(QJsonObject& projectJSON)
{
    int i;

    projectJSON["project_id"] = id;
    projectJSON["title"] = title;
    projectJSON["description"] = description;
    projectJSON["numberOfRegisteredUsers"] = numberOfRegisteredUsers;

    // We dont' need to save PPPs but we do need to save configurations
    QJsonArray configArray;
    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        QJsonObject config;
        projectConfigurations[i].serializeJSONForSave(config);
        configArray.append(config);
    }

    projectJSON["configurations"] = configArray;

    return true;
}

bool Project::deserializeJSONFromRetrieve(const QJsonObject& projectJSON)
{
    int i;

    id = projectJSON.value("project_id").toInt();
    title = projectJSON.value("title").toString();
    description = projectJSON.value("description").toString();
    numberOfRegisteredUsers = projectJSON.value("numberOfRegisteredUsers").toInt();
    QJsonArray configArray = projectJSON["configurations"].toArray();
    for(i=0;i<configArray.size();++i)
    {
        QJsonObject config = configArray[i].toObject();

        projectConfigurations[i].deserializeJSONFromRetrieve(config);
    }

    return true;
}
