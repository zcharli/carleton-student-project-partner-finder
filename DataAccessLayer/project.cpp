#include "project.h"
#include "projectpartnerprofile.h"
#include "studentuser.h"
#include <QJsonArray>

#define NUMBER_OF_CONFIGURATIONS 1

Project::Project(QString title, QString desc)
{
    this->title = title;
    this->description = desc;
    numberOfRegisteredUsers = 0;
    id = 0;
    //initialize configurations array
    projectConfigurations = Configuration::DefaultConfigurations();
}

Project::Project()
{
    numberOfRegisteredUsers = 0;
    id = 0;
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
    // The student count is updated when the request query is successful
    registeredPPPs.insert(profile);
    profile.getStudentUser().addProjectToUser(this->id);
}

void Project::unRegisterPPP(ProjectPartnerProfile& profile)
{
    // The student count is updated when the request query is successful
    registeredPPPs.remove(profile);
    profile.getStudentUser().removeProjectFromUser(this->id);
}

int Project::getNumberOfRegisteredUsers()
{
    return numberOfRegisteredUsers;
}

void Project::setNumberOfRegisteredUsers(int newNum)
{
    // Never called by the database, after successful query, user must update themself
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

void Project::getRegisteredPPPs(QVector<ProjectPartnerProfile*>& listToPopulate)
{
    foreach (ProjectPartnerProfile profile, registeredPPPs)
    {
        listToPopulate.append(&profile);
    }
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

void Project::addPPPtoProject(ProjectPartnerProfile& ppp)
{
    registeredPPPs.insert(ppp);
}

bool Project::serializeJSONForSave(QJsonObject& projectJSON)
{
    int i;
    QJsonArray configArray;
    if(id != 0)
    {
        projectJSON["id"] = id;
    }


    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        QJsonObject config;
        projectConfigurations[i].serializeJSONForSave(config);
        configArray.append(config);
    }
    projectJSON.insert("description", description);
    projectJSON.insert("title", title);
    projectJSON.insert("numberOfRegisteredUsers", numberOfRegisteredUsers);
    projectJSON["configurations"] = configArray;

    return true;
}

bool Project::deserializeJSONFromRetrieve(const QJsonObject& projectJSON)
{
    int i;

    id = projectJSON.value("id").toInt();
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

bool Project::serializeJSONFromCollection(QJsonObject& json, const QVector<Project*>& projectList)
{
    // Probably uneeded function, change this comment when you use this
    QJsonArray projectJSONArray;
    int i;

    for(i=0;i<projectList.size();++i)
    {
        QJsonObject project;
        projectList[i]->serializeJSONForSave(project);
        projectJSONArray.append(project);
    }

    json["count"] = projectList.size();
    json["projects"] = projectJSONArray;
    return true;
}


bool Project::deserializeJSONFromCollection(const QJsonObject& json, QVector<Project*>& projectList)
{
    if(!json.contains("projects"))
    {
        return false;
    }

    QJsonArray projectJSONArray = json["projects"].toArray();
    int i = 0;
    int count = json["count"].toInt();

    for(i=0;i<count;++i)
    {
        Project* project = new Project();
        project->deserializeJSONFromRetrieve(projectJSONArray[i].toObject());
        projectList.append(project);
    }

    return true;
}
