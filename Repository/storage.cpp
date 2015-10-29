#include "storage.h"
#include "Repository/userrepository.h"
#include "Repository/projectrepository.h"
#include "Models/user.h"
#include "Models/project.h"

#define SUCCESS 0
#define INVALID_ACTION -1

Storage* Storage::singletonStorage = 0;

Storage::Storage():repoProject(new ProjectRepository()), repoUser(new UserRepository())
{

}

Storage::~Storage()
{
    delete repoProject;
    delete repoUser;
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

/*  @input: actionToExecute: ActionType (input), User& user, projectProxy: Project& (inout)
 *   @desc: Executes a database action on the provided Project:
 *                  createdProject: saves the created Project entity to the database
 *                    fetchProject: fetches the details of the Project and populates the projectProxy with the details
 *                  updatedProject: saves the changes made by the user to his/her Project (only applies to AdministratorUsers)
 *                discoverProjects: fetches all projects (only applies to StudentUsers)
 *              fetchUsersProjects: fetches the projects that applies to the user
 *                                  (AdministratorUser => created Projects, StudentUser => registereProjects)
 *             registeredInProject: adds the newly registered user to the project in the database
 *         unregisteredFromProject: removes the user from the list of registered users in the database
 */
int executeActionForProject(ActionType, User&, Project&)
{

}
