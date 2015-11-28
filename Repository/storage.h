#ifndef STORAGE_H
#define STORAGE_H

/*  This class acts as Facade to handle all
 *  request to the database from other controll objects
 */
#include <QVector>

//  Forward declarations
class UserRepository;
class ProjectRepository;
class User;
class Project;
class ProjectPartnerProfile;
class DatabaseManager;

enum ActionType
{
    createAcount = 0,
    createdPPP,
    fetchPPP,
    updatedPPP,
    deletedPPP,
    registeredInProject,
    unregisteredFromProject,
    discoverProjects,
    fetchUsersProjects,
    fetchProject,
    createdProject,
    updatedProject,
    fetchPPPsForProject
};

class Storage
{
    Storage();
    ~Storage();

    static Storage *singletonStorage;
    ProjectRepository *repoProject;
    UserRepository *repoUser;
    DatabaseManager *dbManager;

public:
    /*  Returns the single instance of the storage class
     *  Creates an instance if one doesn't exist already
     */
    static Storage& defaultStorage();

    /*  @input: actionToExecute: ActionType (input), User& (student)user, pppProxy: ProjectPartnerProfile& (inout)
     *   @desc: Executes a database action on the provided PPP:
     *          createPPP: saves the created PPP entity to the database
     *           fetchPPP: fetches the details of the PPP for the given User and populates the PPP
     *         updatedPPP: saves the changes made by the user to his/her PPP
     * @output: successStatus: int (0 if true) otherwise returns the error number
     */
    int executeActionForPPP(ActionType, User&, ProjectPartnerProfile&);

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
     * @output: successRate: int (0 if true) otherwise returns the error number
     */
    int executeActionForProject(ActionType, User&, QVector<Project*>&);

    /*   @input: username: QString&, loggedInUser: User& (out param)
     *    @desc: attempts to login user with given username. On success,
     *           the user's details are populated into the user proxy
     *  @output: status: int (success or failure)
     */
    int loginUserWithUsername(QString&, User&);

    /*   @input: signedupUser: User&
     *    @desc: attempts to signup user with given username.
     *  @output: status: int (success or failure)
     */
    int signupUser(User&);

};

#endif // STORAGE_H
