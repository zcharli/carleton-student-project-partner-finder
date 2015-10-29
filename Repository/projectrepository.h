#ifndef PROJECTREPOSITORY_H
#define PROJECTREPOSITORY_H

#include <QVector>
#include <QtSql/QSqlDatabase>

class User;
class Project;

class ProjectRepository
{
public:
    ProjectRepository(QSqlDatabase &db);
    ~ProjectRepository();

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for when the user has created a project
     *      @return: success or failure: bool
     */
    int userCreatedProject(User &user, Project &project);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for fetching the Projects for the user
     *      @return: success or failure: bool
     */
    int fetchProjectForUser(User &user, Project &project);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for when the user updates a project
     *      @return: success or failure: bool
     */
    int userUpdatedProject(User &user, Project &project);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for fetching all projects
     *      @return: success or failure: bool
     */
    int fetchAllProjects(User &user, QVector<Project *>& projects);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for fetching projects for the user
     *      @return: success or failure: bool
     */
    int fetchProjectsForUser(User &user, QVector<Project *>& projects);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for when the user registers in a project
     *      @return: success or failure: bool
     */
    int userRegisteredInProject(User &user, Project &project);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for when the user unregisters from a project
     *      @return: success or failure: bool
     */
    int userUnregisteredFromProject(User &user, Project &project);

    /*!
     *       @param: user: User&, projects: Project&
     *        @desc: handles the database actions necessary for fetching the PPPs for a particular project
     *      @return: success or failure: bool
     */
    int fetchPPPsForProject(User &user, Project &project);

private:
    QSqlDatabase db;
};

#endif // PROJECTREPOSITORY_H
