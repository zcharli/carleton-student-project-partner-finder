#ifndef DATAACCESSFACADE_H
#define DATAACCESSFACADE_H

#include "projectpartnerprofile.h"
#include "projectpartnerprofileproxy.h"
#include "project.h"
#include "Repository/dataaccessdispatcher.h"

#include <QVector>

class User;

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
    fetchUserRecentProjects,
    fetchProject,
    createdProject,
    updatedProject,
    fetchPPPsForProject,
    login,
    createAccount
};

class DataAccessFacade
{
    static DataAccessFacade *dataInstance;

    //  Keep track of already loaded projects and Profiles to prevent
    //  unnecesarrily querrying the database at all times
    QVector<Project*> loadedProjects;
    QVector<ProjectPartnerProfile*> loadedProfiles;

    static QVector<ProjectPartnerProfile*> allocatedProfiles;
    static QVector<Project*> allocatedProjects;
    static QVector<User*> allocatedUsers;

    User *currentUser;
    Project *currentProject;
    DataAccessDispatcher *dispatcher;


public:
    DataAccessFacade();
    ~DataAccessFacade();

    /*  Returns the single instance of the DataAccessFacade class
     *  Creates an instance if one doesn't exist already
     */
    static DataAccessFacade& managedDataAccess();

    static ProjectPartnerProfile* defaultProfile(StudentUser&);
    static Project* defaultProject();
    static User* defaultUser(UserType);

    static void trackAllocatedProject(Project*);
    static void doneUsingProfile(ProjectPartnerProfile*);
    static void doneUsingProject(Project*);
    static void doneUsingUser(User*);

    /*!
     *       @param: none
     *        @desc: returns the Database Dispatcher of the Data Access facade
     *      @return: dispatcher: DataAccessDispatcher&
     */
    DataAccessDispatcher& getDispatcher();

    /*!
     *       @param: none
     *        @desc: returns the current user that is logged in
     *      @return: currentUser pointer: User*
     */
    User* getCurrentUser();

    /*!
     *       @param: currentUser:
     *        @desc: sets the current user for session
     *      @return: void
     */
    void setCurrentUser(User*);

    /*!
     *       @param: none
     *        @desc: returns the current project that is in the session
     *      @return: currentUser pointer: User*
     */
    Project* getCurrentProject();

    /*!
     *       @param: currentUser:
     *        @desc: sets the current project for session
     *      @return: void
     */
    void setCurrentProject(Project*);

    /*!
     *       @param: none
     *        @desc: free the current user from memory, ready to add a new user.
     *      @return: void
     */
    void deleteCurrentUser();

    /*!
     *       @param: none
     *        @desc: free the current project from memory, ready to add a new project.
     *      @return: void
     */
    void deleteCurrentProject();

    /*  @input: actionToExecute: ActionType (input), User& (student)user, pppProxy: ProjectPartnerProfile& (inout)
     *   @desc: Executes a database action on the provided PPP:
     *          createPPP: saves the created PPP entity to the database
     *           fetchPPP: fetches the details of the PPP for the given User and populates the PPP
     *         updatedPPP: saves the changes made by the user to his/her PPP
     * @output: successStatus: int (0 if true) otherwise returns the error number
     */
    int execute(ActionType, User&, ProjectPartnerProfile&);

    /*  @input: actionToExecute: ActionType (input), User& user, project: Project* (inout)
     *   @desc: Executes a database action on the provided Project:
     *                  createdProject: saves the created Project entity to the database
     *                    fetchProject: fetches the details of the Project and populates the projectProxy with the details
     *                  updatedProject: saves the changes made by the user to his/her Project (only applies to AdministratorUsers)
     *             registeredInProject: adds the newly registered user to the project in the database
     *         unregisteredFromProject: removes the user from the list of registered users in the database
     * @output: successRate: int (0 if true) otherwise returns the error number
     */
    int execute(ActionType, User&, Project*);


    /*  @input: actionToExecute: ActionType (input), User& user, projectList: QList<Project*> (inout)
     *   @desc: Executes a database action on the provided Project list:
     *                discoverProjects: fetches all projects (only applies to StudentUsers)
     *              fetchUsersProjects: fetches the projects that applies to the user
     * @output: successRate: int (0 if true) otherwise returns the error number
     */
    int execute(ActionType, User&, QVector<Project*>&);

    /*   @input: actionToExecute: ActionType (input), user: User&
     *    @desc: executes action on the given user
     *  @output: status: int (success or failure)
     */
    int execute(ActionType, User&);


};

#endif // DATAACCESSFACADE_H
