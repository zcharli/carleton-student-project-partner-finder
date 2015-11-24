#include "storage.h"
#include "userrepository.h"
#include "projectrepository.h"
#include "databasemanager.h"

// Subsystem dependencies
#include "DataAccessLayer/Models/user.h"
#include "DataAccessLayer/Models/project.h"

#define SUCCESS 0
#define INVALID_ACTION -1

Storage* Storage::singletonStorage = 0;

Storage::Storage():
    dbManager(new DatabaseManager())
{
    repoProject = new ProjectRepository(dbManager->getDB());
    repoUser = new UserRepository(dbManager->getDB());
}

Storage::~Storage()
{
    delete repoProject;
    delete repoUser;
    delete dbManager;
}

Storage& Storage::defaultStorage()
{
    if(singletonStorage == NULL)
    {
        singletonStorage = new Storage();
    }
    return *singletonStorage;
}


int Storage::executeActionForPPP(ActionType action, User& user, ProjectPartnerProfile& ppp)
{
    int successStatus = SUCCESS;
    switch (action)
    {
        case createdPPP:
            successStatus = repoUser->userCreatedPPP(user, ppp);
            break;
        case fetchPPP:
            successStatus = repoUser->fetchPPPForUser(user, ppp);
            break;
        case updatedPPP:
            successStatus = repoUser->userUpdatedPPP(user, ppp);
            break;
        case deletedPPP:
            successStatus = repoUser->userDeletedPPP(user, ppp);
            break;
        default:
            successStatus = INVALID_ACTION;
            break;
    }
    return successStatus;
}

/*   @input: username: QString&, loggedInUser: User& (out param)
 *    @desc: attempts to login user with given username. On success,
 *           the user's details are populated into the user proxy
 *  @output: status: int (success or failure)
 */
int Storage::loginUserWithUsername(QString& username, User& user)
{
    return repoUser->retrieveUserWithUsername(username, user, user.getUserType());
}

/*   @input: signedupUser: User&
 *    @desc: attempts to signup user with given username.
 *  @output: status: int (success or failure)
 */
int Storage::signupUser(User& user)
{
    return repoUser->createUser(user);
}

int Storage::executeActionForProject(ActionType action, User& user, QVector<Project*>& projects)
{
    int successStatus = SUCCESS;

    switch(action)
    {
        case createdProject:
            successStatus = repoProject->userCreatedProject(user, *(projects[0]));
            break;
        case fetchProject:
            successStatus = repoProject->fetchProjectForUser(user, *(projects[0]));
            break;
        case updatedProject:
            successStatus = repoProject->userUpdatedProject(user, *(projects[0]));
            break;
        case discoverProjects:
            successStatus = repoProject->fetchAllProjects(user, projects);
            break;
        case fetchUsersProjects:
            successStatus = repoProject->fetchProjectsForUser(user, projects);
            break;
        case registeredInProject:
            successStatus = repoProject->userRegisteredInProject(user, *(projects[0]));
            break;
        case unregisteredFromProject:
            successStatus = repoProject->userUnregisteredFromProject(user, *(projects[0]));
            break;
        case fetchPPPsForProject:
            successStatus = repoProject->fetchPPPsForProject(user, *(projects[0]));
            break;
        default:
            successStatus = INVALID_ACTION;
    }

    return successStatus;
}
