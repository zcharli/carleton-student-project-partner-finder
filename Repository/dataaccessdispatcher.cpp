#include "dataaccessdispatcher.h"
#include "userrepository.h"
#include "projectrepository.h"
#include "databasemanager.h"

#include "errorcodes.h"
#include <QJsonObject>
#include <QDebug>

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

int DataAccessDispatcher::retrieveAllProjects(QJsonObject& fillMeUp)
{
    if(repoProject->fetchAllProjects(fillMeUp) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }

    return SUCCESS;
}

int DataAccessDispatcher::retrieveProjectUsingID(QJsonObject& inProjectOutProjects)
{
    // Not used currently since all projects are loaded at once
    int projectId;

    if((projectId = getProjectIdFromJson(inProjectOutProjects)) == 0)
    {
        return NO_PROJECT_ID;
    }

    if(repoProject->fetchProjectForUser(inProjectOutProjects, projectId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }

    return SUCCESS;
}
int DataAccessDispatcher::retrieveProjectsForUser(QJsonObject& inUserOutProjects)
{
    int userId;

    if((userId = getUserIdFromJson(inUserOutProjects)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoProject->fetchProjectsForUser(inUserOutProjects, userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }

    return SUCCESS;
}

int DataAccessDispatcher::retrievePPPsForProject(QJsonObject& inUserOutPPP)
{
    int projectId;
    if((projectId = getProjectIdFromJson(inUserOutPPP)) == 0)
    {
        return NO_PROJECT_ID;
    }

    if(repoProject->fetchPPPsForProject(inUserOutPPP, projectId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::retrieveUserWithUsername(QJsonObject& inUserOutUser)
{
    QString userName;
    int type;
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
        return NO_USERNAME;
    }

    if(!inUserOutUser.contains("userType"))
    {
        return NO_USER_TYPE;
    }

    type = inUserOutUser["userType"].toInt();

    if(repoUser->retrieveUserWithUsername(inUserOutUser, userName, type) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::retrievePPPForUser(QJsonObject& inUserOutPPP)
{
    int pppId;

    if((pppId = getPPPIdFromJson(inUserOutPPP)) == 0)
    {
        return NO_PPP_ID;
    }

    if(repoUser->fetchPPPForUser(inUserOutPPP, pppId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}

int DataAccessDispatcher::userCreatedPPP(QJsonObject& inUserinPPP)
{
    int userId;
    if((userId = getUserIdFromJson(inUserinPPP)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoUser->userCreatedPPP(inUserinPPP,userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::userUpdatedPPP(QJsonObject& inUserinPPP)
{
    if(repoUser->userUpdatedPPP(inUserinPPP) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::userDeletedPPP(QJsonObject& inUserinPPP)
{
    int userId;
    if((userId = getUserIdFromJson(inUserinPPP)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoUser->userDeletedPPP(userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::createUser(QJsonObject& inUser)
{
    if(repoUser->createUser(inUser) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::userCreatedProject(QJsonObject& inProjectinUser)
{
    int userId;
    if((userId = getUserIdFromJson(inProjectinUser)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoProject->userCreatedProject(inProjectinUser,userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::userUpdatedProject(QJsonObject& inProjectinUser)
{
    int userId;
    if((userId = getUserIdFromJson(inProjectinUser)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoProject->userUpdatedProject(inProjectinUser,userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }
    return SUCCESS;
}
int DataAccessDispatcher::userRegisteredInProject(QJsonObject& inProjectinUser)
{
    // Notice: Please remember to update registered user count after this returns successful
    int userId;
    int projectId;

    if(!inProjectinUser.contains("project") || !inProjectinUser.contains("user") ||
            ((projectId = getProjectIdFromJson(inProjectinUser)) == 0) ||
            ((userId = getUserIdFromJson(inProjectinUser)) == 0))
    {
        return UNKNOWN_ERROR;
    }

    if(repoProject->userRegisteredInProject(projectId,userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }

    return SUCCESS;
}
int DataAccessDispatcher::userUnRegisteredInProject(QJsonObject& inProjectinUser)
{
    // Notice: Please remember to update registered user count after this returns successful
    int userId;
    int projectId;

    if(!inProjectinUser.contains("project") ||
            ((projectId = getProjectIdFromJson(inProjectinUser)) == 0) ||
            ((userId = getUserIdFromJson(inProjectinUser)) == 0))
    {
        return UNKNOWN_ERROR;
    }

    QJsonObject project = inProjectinUser.value("project").toObject();

    if(project["numberOfRegisteredUsers"].toInt() == 0)
    {
        return NO_REGISTERED_STUDENTS;
    }

    if(repoProject->userUnregisteredFromProject(projectId,userId) != SUCCESS)
    {
        return DATABASE_QUERY_ERROR;
    }

    return SUCCESS;
}

int DataAccessDispatcher::getUserIdFromJson(QJsonObject& json)
{
    if(json.contains("user_id"))
    {
        return json.value("user_id").toInt();
    }
    else if(json.contains("id"))
    {
        return json.value("id").toInt();
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
    else if(json.contains("id"))
    {
        return json.value("id").toInt();
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

int DataAccessDispatcher::getPPPIdFromJson(QJsonObject& json)
{
    if(json.contains("pppID"))
    {
        return json.value("pppID").toInt();
    }
    else if(json.contains("pppIDForFetch"))
    {
        return json["pppIDForFetch"].toInt();
    }
    else if(json.contains("user"))
    {
        return json["user"].toObject()["ppp"].toObject()["pppIDForFetch"].toInt();
    }
    else if(json.contains("ppp"))
    {
        return json["ppp"].toObject()["pppIDForFetch"].toInt();
    }
    else
    {
        return 0;
    }
}
