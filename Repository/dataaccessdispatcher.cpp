#include "dataaccessdispatcher.h"
#include "userrepository.h"
#include "projectrepository.h"
#include "databasemanager.h"

#include <QJsonObject>

#define SUCCESS 0
#define INVALID_ACTION -1

DataAccessDispatcher::DataAccessDispatcher():
    dbManager(new DatabaseManager())
{
    repoProject = new ProjectRepository(dbManager->getDB());
    repoUser = new UserRepository(dbManager->getDB());
}

DataAccessDispatcher::~DataAccessDispatcher()
{
    delete repoProject;
    delete repoUser;
    delete dbManager;
}

void DataAccessDispatcher::clearJsonObject(QJsonObject& cleanMe)
{
    QJsonObject::iterator it;
    for (it = cleanMe.begin(); it != cleanMe.end(); it++) {
        // Require an empty object
        cleanMe.remove(it.key());
    }
}

bool DataAccessDispatcher::retrieveAllProjects(QJsonObject& fillMeUp)
{
    if(!fillMeUp.isEmpty())
    {
       clearJsonObject(fillMeUp);
    }

    if(repoProject->fetchAllProjects(fillMeUp) != SUCCESS)
    {
        return false;
    }

    return true;
}

bool DataAccessDispatcher::retrieveProjectUsingID(QJsonObject& inProjectOutProjects)
{
    // Not used currently since all projects are loaded at once
    int projectId;

    if((projectId = getProjectIdFromJson(inProjectOutProjects)) == 0)
    {
        return false;
    }

    clearJsonObject(inProjectOutProjects);

    if(repoProject->fetchProjectForUser(inProjectOutProjects, projectId) != SUCCESS)
    {
        return false;
    }

    return true;
}
bool DataAccessDispatcher::retrieveProjectsForUser(QJsonObject& inUserOutProjects)
{
    int userId;

    if((userId = getUserIdFromJson(inUserOutProjects)) == 0)
    {
        return false;
    }

    clearJsonObject(inUserOutProjects);

    if(repoProject->fetchProjectsForUser(inUserOutProjects, userId) != SUCCESS)
    {
        return false;
    }

    return true;
}

bool DataAccessDispatcher::retrievePPPsForProject(QJsonObject& inUserOutPPP)
{
    int projectId;
    if((projectId = getProjectIdFromJson(inUserOutPPP)) == 0)
    {
        return false;
    }

    clearJsonObject(inUserOutPPP);

    if(repoProject->fetchPPPsForProject(inUserOutPPP, projectId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::retrieveUserWithUsername(QJsonObject& inUserOutUser)
{
    QString userName;
    if(inUserOutUser.contains("userName"))
    {
        userName = inUserOutUser.value("userName").toString();
    }
    else if(inUserOutUser.contains("user"))
    {
        userName = inUserOutUser["user"].toObject()["userName"].toString();
    }
    else
    {
        return false;
    }

    clearJsonObject(inUserOutUser);

    if(repoUser->retrieveUserWithUsername(inUserOutUser, userName) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::retrievePPPForUser(QJsonObject& inUserOutPPP)
{
    int userId;

    if((userId = getUserIdFromJson(inUserOutPPP)) == 0)
    {
        return false;
    }

    clearJsonObject(inUserOutPPP);

    if(repoUser->fetchPPPForUser(inUserOutPPP, userId) != SUCCESS)
    {
        return false;
    }
    return true;
}

bool DataAccessDispatcher::userCreatedPPP(QJsonObject& inUserinPPP)
{
    int userId;
    if((userId = getUserIdFromJson(inUserinPPP)) == 0)
    {
        return false;
    }

    if(repoUser->userCreatedPPP(inUserinPPP,userId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::userUpdatedPPP(QJsonObject& inUserinPPP)
{
    int userId;
    if((userId = getUserIdFromJson(inUserinPPP)) == 0)
    {
        return false;
    }

    if(repoUser->userUpdatedPPP(inUserinPPP,userId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::userDeletedPPP(QJsonObject& inUserinPPP)
{
    int userId;
    if((userId = getUserIdFromJson(inUserinPPP)) == 0)
    {
        return false;
    }

    if(repoUser->userDeletedPPP(inUserinPPP,userId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::createUser(QJsonObject& inUser)
{
    if(repoUser->createUser(inUser) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::userCreatedProject(QJsonObject& inProjectinUser)
{
    int userId;
    if((userId = getUserIdFromJson(inProjectinUser)) == 0)
    {
        return false;
    }

    if(repoProject->userCreatedProject(inProjectinUser,userId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::userUpdatedProject(QJsonObject& inProjectinUser)
{
    int userId;
    if((userId = getUserIdFromJson(inProjectinUser)) == 0)
    {
        return false;
    }

    if(repoProject->userUpdatedProject(inProjectinUser,userId) != SUCCESS)
    {
        return false;
    }
    return true;
}
bool DataAccessDispatcher::userRegisteredInProject(QJsonObject& inProjectinUser)
{
    int userId;
    int projectId;

    if(!inProjectinUser.contains("project") ||
            ((projectId = getProjectIdFromJson(inProjectinUser)) == 0) ||
            ((userId = getUserIdFromJson(inProjectinUser)) == 0))
    {
        return false;
    }

    if(repoProject->userRegisteredInProject(projectId,userId) != SUCCESS)
    {
        return false;
    }
    // We know its succesful now so we can add num user registered
    QJsonObject project = inProjectinUser.value("project").toObject();

    inProjectinUser["project"].toObject()["numberOfRegisteredUsers"] = project.value("numberOfRegisteredUsers").toInt() + 1;

    return true;
}
bool DataAccessDispatcher::userUnRegisteredInProject(QJsonObject& inProjectinUser)
{
    int userId;
    int projectId;


    if(!inProjectinUser.contains("project") ||
            ((projectId = getProjectIdFromJson(inProjectinUser)) == 0) ||
            ((userId = getUserIdFromJson(inProjectinUser)) == 0))
    {
        return false;
    }

    QJsonObject project = inProjectinUser.value("project").toObject();

    if(project["numberOfRegisteredUsers"].toInt() == 0)
    {
        return false;
    }

    if(repoProject->userUnregisteredFromProject(projectId,userId) != SUCCESS)
    {
        return false;
    }
    // We know its succesful now so we can add num user registered
    inProjectinUser["project"].toObject()["numberOfRegisteredUsers"] = project.value("numberOfRegisteredUsers").toInt() - 1;

    return true;
}

int DataAccessDispatcher::getUserIdFromJson(QJsonObject& json)
{
    if(json.contains("user_id"))
    {
        return json.value("user_id").toInt();
    }
    else if(json.contains("user"))
    {
        return json["user"].toObject()["id"].toInt();
    }
    else if(json.contains("ppp"))
    {
        return json["ppp"].toObject()["user"].toObject()["id"].toInt();
    }
    else
    {
        return 0;
    }
}


int DataAccessDispatcher::getProjectIdFromJson(QJsonObject& json)
{
    if(json.contains("project_id"))
    {
        return json.value("project_id").toInt();
    }
    else if(json.contains("project"))
    {
        return json["project"].toObject()["id"].toInt();
    }
    else
    {
        return 0;
    }
}
