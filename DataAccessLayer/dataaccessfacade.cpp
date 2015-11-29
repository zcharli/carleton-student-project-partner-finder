#include "dataaccessfacade.h"
#include "studentuser.h"
#include "administratoruser.h"

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
    project->serializeJSONForSave(inUserIDInProjectJson);
    user.serializeJSONForSave(userJson);
    inUserIDInProjectJson["user"] = userJson;
    qDebug() << inUserIDInProjectJson["user"].toString();
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
            //successStatus = repoProject->userRegisteredInProject(user, *(projects[0]));
            break;
        case unregisteredFromProject:
            //successStatus = repoProject->userUnregisteredFromProject(user, *(projects[0]));
            break;
        case fetchPPPsForProject:
            //successStatus = repoProject->fetchPPPsForProject(user, *(projects[0]));
            break;
        default:
            successStatus = INVALID_ACTION;
    }
    if (successStatus == SUCCESS)
        project->deserializeJSONFromRetrieve(inUserIDInProjectJson);

    return successStatus;
}

int DataAccessFacade::execute(ActionType action, User& user, QVector<Project*> projectList)
{

    int successStatus = SUCCESS;

    switch(action)
    {
        case discoverProjects:
            //successStatus = repoProject->fetchAllProjects(user, projects);
            break;
        case fetchUsersProjects:
            //successStatus = repoProject->fetchProjectsForUser(user, projects);
            break;
        default:
            successStatus = INVALID_ACTION;
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
