#include "dataaccessfacade.h"
#include "studentuser.h"
#include "administratoruser.h"
#include "DataAccessLayer/mapconfigs.h"

#include <QDebug>

#define SUCCESS 0
#define INVALID_ACTION -1

DataAccessFacade* DataAccessFacade::dataInstance = 0;
QVector<Project*> DataAccessFacade::allocatedProjects;
QVector<ProjectPartnerProfile*> DataAccessFacade::allocatedProfiles;
QVector<User*> DataAccessFacade::allocatedUsers;

DataAccessFacade::DataAccessFacade()
{
    // Create singleton instance
    dispatcher = new DataAccessDispatcher();
    currentProject = NULL;
    currentUser = NULL;
}

DataAccessFacade::~DataAccessFacade()
{
  //  Clean up
  delete dispatcher;
}

void DataAccessFacade::setCurrentUser(User* userToSet)
{
    currentUser = userToSet;
}

void DataAccessFacade::setCurrentProject(Project* projectToSet)
{
    currentProject = projectToSet;
}

void DataAccessFacade::deleteCurrentUser()
{
    if(currentUser != NULL)
    {
        delete currentUser;
        currentUser = NULL;
    }
}

void DataAccessFacade::deleteCurrentProject()
{
    if(currentProject != NULL)
    {
        delete currentProject;
        currentProject = NULL;
    }
}

User* DataAccessFacade::getCurrentUser()
{
    return currentUser;
}

Project* DataAccessFacade::getCurrentProject()
{
    return currentProject;
}

ProjectPartnerProfile* DataAccessFacade::defaultProfile(StudentUser& user)
{

    ProjectPartnerProfileProxy* profile = new ProjectPartnerProfileProxy(user, 0, 0, 0);
    allocatedProfiles.append(profile);
    return profile;
}

DataAccessDispatcher& DataAccessFacade::getDispatcher()
{
    return *dispatcher;
}

Project* DataAccessFacade::defaultProject()
{
    Project* project = new Project(QString(""), QString(""));
    allocatedProjects.append(project);
    return project;
}

User* DataAccessFacade::defaultUser(UserType type)
{
    User *user = NULL;
    QString fname, lname, username = "";
    switch(type)
    {
        case Administrator:
            user = new AdministratorUser(fname, lname, username);
            break;
        case Student:
            user = new StudentUser(fname, lname, username);
            break;
    }
    allocatedUsers.append(user);
    return user;
}

void DataAccessFacade::doneUsingProfile(ProjectPartnerProfile* profile)
{
    int index = allocatedProfiles.indexOf(profile);
    if(index != -1)
    {
        allocatedProfiles.remove(index);
        delete profile;
        profile = NULL;
    }
}

void DataAccessFacade::doneUsingProject(Project* project)
{
    int index = allocatedProjects.indexOf(project);
    if(index != -1)
    {
        allocatedProjects.remove(index);
        delete project;
        project = NULL;
    }
}

void DataAccessFacade::doneUsingUser(User* user)
{
    int index = allocatedUsers.indexOf(user);
    if(index != -1)
    {
        allocatedUsers.remove(index);
        delete user;
        user = NULL;
    }
}

DataAccessFacade& DataAccessFacade::managedDataAccess()
{
    if(dataInstance == NULL)
    {
        dataInstance = new DataAccessFacade();
    }
    return *dataInstance;
}

int DataAccessFacade::execute(ActionType action, User& user, ProjectPartnerProfile& profile)
{
    int successStatus = SUCCESS;
    QJsonObject profileJson;
    profile.serializeJSONForSave(profileJson);
    profileJson[FLOATING_USR_ID] = user.getUserId();
    switch (action)
    {
        case createdPPP:
            successStatus = dispatcher->userCreatedPPP(profileJson);
            break;
        case fetchPPP:
            successStatus = dispatcher->retrievePPPForUser(profileJson);
            break;
        case updatedPPP:
            successStatus = dispatcher->userUpdatedPPP(profileJson);
            break;
        case deletedPPP:
            //successStatus = repoUser->userDeletedPPP(user, ppp);
            break;
        default:
            successStatus = INVALID_ACTION;
            break;
    }
    if(successStatus == SUCCESS)
        profile.deserializeJSONFromRetrieve(profileJson);
    return successStatus;
}

int DataAccessFacade::execute(ActionType action, User& user, Project* project)
{
    int successStatus = SUCCESS;
    QJsonObject inUserIDInProjectJson;
    QJsonObject userJson;
    QJsonObject projectJson;
    project->serializeJSONForSave(projectJson);
    user.serializeJSONForSave(userJson);
    inUserIDInProjectJson[USER_KEY] = userJson;
    inUserIDInProjectJson[PROJECT_KEY] = projectJson;
    switch(action)
    {
        case createdProject:
            successStatus = dispatcher->userCreatedProject(inUserIDInProjectJson);
            break;
        case fetchProject:
            successStatus = dispatcher->retrieveProjectUsingID(inUserIDInProjectJson);
            break;
        case updatedProject:
            successStatus = dispatcher->userUpdatedProject(inUserIDInProjectJson);
            break;
        case registeredInProject:
            successStatus = dispatcher->userRegisteredInProject(inUserIDInProjectJson);
            break;
        case unregisteredFromProject:
            successStatus = dispatcher->userUnRegisteredInProject(inUserIDInProjectJson);
            break;
        case fetchPPPsForProject:
            //successStatus = repoProject->fetchPPPsForProject(user, *(projects[0]));
            break;
        default:
            successStatus = INVALID_ACTION;
    }
    if (successStatus == SUCCESS)
        project->deserializeJSONFromRetrieve(inUserIDInProjectJson[PROJECT_KEY].toObject());

    return successStatus;
}

int DataAccessFacade::execute(ActionType action, User& user, QVector<Project*>& projectList)
{
    int successStatus = SUCCESS;
    QJsonObject projects;
    projects[FLOATING_USR_ID] = user.getUserId();
    switch(action)
    {
        case discoverProjects:
            successStatus = dispatcher->retrieveAllProjects(projects);
            break;
        case fetchUsersProjects:
            successStatus = dispatcher->retrieveProjectsForUser(projects);
            break;
        case fetchUserRecentProjects:
            successStatus = dispatcher->retrieveProjectsForUser(projects, 3);
            break;
        default:
            successStatus = INVALID_ACTION;
    }

    if(successStatus == SUCCESS)
    {
        Project::deserializeJSONFromCollection(projects, projectList);

    }
    return successStatus;
}

int DataAccessFacade::execute(ActionType action, User& user)
{
  int successStatus = SUCCESS;
  QJsonObject userJson;
  user.serializeJSONForSave(userJson);
  switch (action)
  {
      case createAccount:
          successStatus = dispatcher->createUser(userJson);
          break;
      case login:
          successStatus = dispatcher->retrieveUserWithUsername(userJson);
          break;
      default:
          successStatus = INVALID_ACTION;
          break;
  }

  if (successStatus == SUCCESS)
      user.deserializeJSONFromRetrieve(userJson);
  return successStatus;
}
