#include "dataaccessfacade.h"
#include "studentuser.h"
#include "administratoruser.h"

#define SUCCESS 0
#define INVALID_ACTION -1

DataAccessFacade* DataAccessFacade::dataInstance = 0;
QVector<Project*> DataAccessFacade::allocatedProjects;
QVector<ProjectPartnerProfile*> DataAccessFacade::allocatedProfiles;

DataAccessFacade::DataAccessFacade()
{
  // Create singleton instance
  currentUser = NULL;
}

DataAccessFacade::~DataAccessFacade()
{
  //  Clean up
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

    ProjectPartnerProfileProxy* profile = new ProjectPartnerProfileProxy(user);
    allocatedProfiles.append(profile);
    return profile;
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
    switch (action)
    {
        case createdPPP:
            //successStatus = repoUser->userCreatedPPP(user, ppp);
            break;
        case fetchPPP:
            //successStatus = repoUser->fetchPPPForUser(user, ppp);
            break;
        case updatedPPP:
            //successStatus = repoUser->userUpdatedPPP(user, ppp);
            break;
        case deletedPPP:
            //successStatus = repoUser->userDeletedPPP(user, ppp);
            break;
        default:
            successStatus = INVALID_ACTION;
            break;
    }
    return successStatus;
}

int DataAccessFacade::execute(ActionType action, User& user, Project* project)
{
    int successStatus = SUCCESS;

    switch(action)
    {
        case createdProject:
            //successStatus = repoProject->userCreatedProject(user, *(projects[0]));
            break;
        case fetchProject:
            //successStatus = repoProject->fetchProjectForUser(user, *(projects[0]));
            break;
        case updatedProject:
            //successStatus = repoProject->userUpdatedProject(user, *(projects[0]));
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
  switch (action)
  {
      case createAccount:
          //successStatus = repoUser->userCreatedPPP(user, ppp);
          break;
      case login:
          //successStatus = repoUser->fetchPPPForUser(user, ppp);
          break;
      default:
          successStatus = INVALID_ACTION;
          break;
  }
  return successStatus;
}
