#ifndef PROJECTREPOSITORY_H
#define PROJECTREPOSITORY_H

#include <QtSql/QSqlDatabase>

class QJsonObject;

class ProjectRepository
{
public:
    ProjectRepository(QSqlDatabase &db);
    ~ProjectRepository();

    /*!
     *       @param: project: QJsonObject&, userId: int
     *        @desc: handles the database actions necessary for when the user has created a project
     *      @return: success or failure: bool
     */
    int userCreatedProject(QJsonObject& project, int userId);

    /*!
     *       @param: user: QJsonObject& projects: QJsonObject&, int projectID : int
     *        @desc: handles the database actions necessary for fetching the Projects for the user
     *      @return: success or failure: bool
     */
    int fetchProjectForUser(QJsonObject& projectReturn, int projectId);

    /*!
     *       @param: projects: QJsonObject&, userId: int
     *        @desc: handles the database actions necessary for when the user updates a project
     *      @return: success or failure: bool
     */
    int userUpdatedProject(QJsonObject& project, int userId);

    /*!
     *       @param: user: QJsonObject& projects: QJsonObject&
     *        @desc: handles the database actions necessary for fetching all projects
     *      @return: success or failure: bool
     */
    int fetchAllProjects(QJsonObject& projects);

    /*!
     *       @param: user: QJsonObject& projects: QJsonObject&, int userID : int
     *        @desc: handles the database actions necessary for fetching projects for the user
     *      @return: success or failure: bool
     */
    int fetchProjectsForUser(QJsonObject& projectsReturn, int userId, int limit);

    /*!
     *       @param: projectId : int, userId : int, limitOfProjects: int
     *        @desc: handles the database actions necessary for when the user registers in a project
     *      @return: success or failure: bool
     */
    int userRegisteredInProject(int projectId, int userId);

    /*!
     *       @param: projectId : int, userId : int
     *        @desc: handles the database actions necessary for when the user unregisters from a project
     *      @return: success or failure: bool
     */
    int userUnregisteredFromProject(int projectId, int userId);

    /*!
     *       @param: user: QJsonObject&, projectId: int
     *        @desc: handles the database actions necessary for fetching the PPPs for a particular project
     *      @return: success or failure: bool
     */
    int fetchPPPsForProject(QJsonObject& ppp, int projectId);

private:
    QSqlDatabase db;
};

#endif // PROJECTREPOSITORY_H
