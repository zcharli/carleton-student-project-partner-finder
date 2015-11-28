#ifndef DATAACCESSDISPATCHER_H
#define DATAACCESSDISPATCHER_H

class DatabaseManager;
class ProjectRepository;
class UserRepository;
class QJsonObject;

class DataAccessDispatcher
{
    DatabaseManager *dbManager;
    ProjectRepository *repoProject;
    UserRepository *repoUser;

public:
    DataAccessDispatcher();
    ~DataAccessDispatcher();

    /*!
     *  Data Retrieval Services
     */

    /*!  @input: empty map reference: QJsonObject&
     *    @desc: retreives all projects from the database and builds
     *           a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrieveAllProjects(QJsonObject&);

    /*!  @input: single mappable project object with id: QJsonObject&
     *    @desc: retreives a projects from the database by id and builds
     *           a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrieveProjectUsingID(QJsonObject&);

    /*!  @input: single user mappable object with id: QJsonObject&
     *    @desc: retreives projects from the database that is associated to
     *           this user and builds a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrieveProjectsForUser(QJsonObject&);

    /*!  @input: single project mappable object with id: QJsonObject&
     *    @desc: retreives all PPPs registered to this project from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrievePPPsForProject(QJsonObject&);

    /*!  @input: single object with username: QJsonObject&
     *    @desc: retreives all PPPs registered to this project from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrieveUserWithUsername(QJsonObject&);

    /*!  @input: single mappable user object: QJsonObject&
     *    @desc: retreives the user's PPPs from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: int (success or failure)
     */
    int retrievePPPForUser(QJsonObject&);

    /*!
     *  Data Storage Services
     */

    /*!   @input: a mappable user and PPP object: QJsonObject&
     *    @desc: saves the new PPP for the user into the database
     *  @output: status: int (success or failure)
     */
    int userCreatedPPP(QJsonObject&);

    /*!  @input: a mappable user and PPP object: QJsonObject&
     *    @desc: updates the existing PPP for the user into the database
     *  @output: status: int (success or failure)
     */
    int userUpdatedPPP(QJsonObject&);

    /*!  @input: a mappable user and PPP object: QJsonObject&
     *    @desc: deletes the PPP for the user into the database
     *  @output: status: int (success or failure)
     */
    int userDeletedPPP(QJsonObject&);

    /*!  @input: a mappable user object: QJsonObject&
     *    @desc: saves the new user into the database
     *  @output: status: int (success or failure)
     */
    int createUser(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: saves the new project for the user into the database
     *  @output: status: int (success or failure)
     */
    int userCreatedProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: updates the existing project for the user into the database
     *  @output: status: int (success or failure)
     */
    int userUpdatedProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: registered user into the project saves the record into the database
     *  @output: status: int (success or failure)
     */
    int userRegisteredInProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: unregistered user from the project saves the record into the database
     *  @output: status: int (success or failure)
     */
    int userUnRegisteredInProject(QJsonObject&);

private:

    /*!  @input: a JSON request object: QJsonObject&
     *    @desc: searches through the request object to try to find a user id
     *  @output: id: int (success->id or failure->0)
     */
    int getUserIdFromJson(QJsonObject&);

    /*!  @input: a JSON request object: QJsonObject&
     *    @desc: searches through the request object to try to find a project id
     *  @output: id: int (success->id or failure->0)
     */
    int getProjectIdFromJson(QJsonObject&);

    /*!  @input: a JSON request object: QJsonObject&
     *    @desc: searches through the request object to try to find a ppp id
     *  @output: id: int (success->id or failure->0)
     */
    int getPPPIdFromJson(QJsonObject&);
};

#endif // DATAACCESSDISPATCHER_H
