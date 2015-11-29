#include "project.h"
#include "projectpartnerprofile.h"
#include "projectpartnerprofileproxy.h"
#include "studentuser.h"
#include "DataAccessLayer/dataaccessfacade.h"
#include "mapconfigs.h"
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

Project::Project(const QJsonObject& projectJSON)
{
    numberOfRegisteredUsers = 0;
    id = 0;
    projectConfigurations = Configuration::DefaultConfigurations();
    deserializeJSONFromRetrieve(projectJSON);
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
    numberOfRegisteredUsers++;
    profile.getStudentUser().addProjectToUser(this->id);
}

void Project::unRegisterPPP(ProjectPartnerProfile& profile)
{
    // The student count is updated when the request query is successful
    registeredPPPs.remove(profile);
    numberOfRegisteredUsers--;
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
        projectJSON[PROJECT_id] = id;
    }


    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        QJsonObject config;
        projectConfigurations[i].serializeJSONForSave(config);
        configArray.append(config);
    }
    projectJSON.insert(PROJECT_description, description);
    projectJSON.insert(PROJECT_title, title);
    projectJSON.insert(PROJECT_numberOfRegisteredUsers, numberOfRegisteredUsers);
    projectJSON[PROJECT_configuration] = configArray;

    return true;
}

bool Project::deserializeJSONFromRetrieve(const QJsonObject& projectJSON)
{
    if(projectJSON.isEmpty())
    {
        return false;
    }

    int i;

    id = projectJSON.value(PROJECT_id).toInt();
    title = projectJSON.value(PROJECT_title).toString();
    description = projectJSON.value(PROJECT_description).toString();
    numberOfRegisteredUsers = projectJSON.value(PROJECT_numberOfRegisteredUsers).toInt();

    QJsonArray configArray = projectJSON[PROJECT_configuration].toArray();
    for(i=0;i<configArray.size();++i)
    {
        QJsonObject config = configArray[i].toObject();

        projectConfigurations[i].deserializeJSONFromRetrieve(config);
    }

    if(projectJSON.contains(PPP_KEY))
    {
        QJsonArray registeredPPPList = projectJSON[PPP_KEY].toObject()[PPP_KEY].toArray();

        for(i=0;i<registeredPPPList.size();++i)
        {
            User* stuUser = DataAccessFacade::defaultUser(Student);
            ProjectPartnerProfile* profile = DataAccessFacade::defaultProfile((*((StudentUser*)stuUser)));
            profile->deserializeJSONFromRetrieve(registeredPPPList[i].toObject());
            registeredPPPs.insert(*profile);

            // we copied these things so we can delete them into the
            delete profile;
            delete stuUser;
        }
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

    json[COUNT_KEY] = projectList.size();
    json[PROJECTS_KEY] = projectJSONArray;
    return true;
}


bool Project::deserializeJSONFromCollection(const QJsonObject& json, QVector<Project*>& projectList)
{
    if(!json.contains(PROJECTS_KEY))
    {
        return false;
    }

    QJsonArray projectJSONArray = json[PROJECTS_KEY].toArray();
    int i = 0;
    int count = json[COUNT_KEY].toInt();

    for(i=0;i<count;++i)
    {
        Project* project = new Project(projectJSONArray[i].toObject());
        projectList.append(project);
    }

    return true;
}
