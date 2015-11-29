#include "dataaccessdispatcher.h"
#include "userrepository.h"
#include "projectrepository.h"
#include "databasemanager.h"
#include "DataAccessLayer/mapconfigs.h"
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
int DataAccessDispatcher::retrieveProjectsForUser(QJsonObject& inUserOutProjects, int limit = 0)
{
    int userId;

    if((userId = getUserIdFromJson(inUserOutProjects)) == 0)
    {
        return NO_USER_ID;
    }

    if(repoProject->fetchProjectsForUser(inUserOutProjects, userId, limit) != SUCCESS)
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
    if(inUserOutUser.contains(USER_userName))
    {
        userName = inUserOutUser.value(USER_userName).toString();
    }
    else if(inUserOutUser.contains(USER_KEY))
    {
        userName = inUserOutUser[USER_KEY].toObject()[USER_userName].toString();
    }
    else
    {
        return NO_USERNAME;
    }

    if(!inUserOutUser.contains(USER_userType))
    {
        return NO_USER_TYPE;
    }

    type = inUserOutUser[USER_userType].toInt();

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

    if(!inProjectinUser.contains(PROJECT_KEY) || !inProjectinUser.contains(USER_KEY) ||
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

    if(!inProjectinUser.contains(PROJECT_KEY) ||
            ((projectId = getProjectIdFromJson(inProjectinUser)) == 0) ||
            ((userId = getUserIdFromJson(inProjectinUser)) == 0))
    {
        return UNKNOWN_ERROR;
    }

    QJsonObject project = inProjectinUser.value(PROJECT_KEY).toObject();

    if(project[PROJECT_numberOfRegisteredUsers].toInt() == 0)
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
    if(json.contains(FLOATING_USR_ID))
    {
        return json.value(FLOATING_USR_ID).toInt();
    }
    else if(json.contains(GENERIC_OBJ_ID))
    {
        return json.value(GENERIC_OBJ_ID).toInt();
    }
    else if(json.contains(USER_KEY))
    {
        return json[USER_KEY].toObject()[GENERIC_OBJ_ID].toInt();
    }
    else if(json.contains(PPP_pppID))
    {
        return json[PPP_pppID].toObject()[USER_KEY].toObject()[GENERIC_OBJ_ID].toInt();
    }
    else
    {
        return 0;
    }
}

int DataAccessDispatcher::getProjectIdFromJson(QJsonObject& json)
{
    if(json.contains(FLOATING_PRJ_ID))
    {
        return json.value(FLOATING_PRJ_ID).toInt();
    }
    else if(json.contains(GENERIC_OBJ_ID))
    {
        return json.value(GENERIC_OBJ_ID).toInt();
    }
    else if(json.contains(PROJECT_KEY))
    {
        return json[PROJECT_KEY].toObject()[GENERIC_OBJ_ID].toInt();
    }
    else
    {
        return 0;
    }
}

int DataAccessDispatcher::getPPPIdFromJson(QJsonObject& json)
{
    if(json.contains(PPP_pppID))
    {
        return json.value(PPP_pppID).toInt();
    }
    else if(json.contains(STUDENT_pppIDForFetch))
    {
        return json[STUDENT_pppIDForFetch].toInt();
    }
    else if(json.contains(USER_KEY))
    {
        return json[USER_KEY].toObject()[PPP_pppID].toObject()[STUDENT_pppIDForFetch].toInt();
    }
    else if(json.contains(PPP_pppID))
    {
        return json[PPP_pppID].toObject()[STUDENT_pppIDForFetch].toInt();
    }
    else
    {
        return 0;
    }
}
