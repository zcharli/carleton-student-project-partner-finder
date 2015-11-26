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
     *  @output: status: bool (success or failure)
     */
    bool retrieveAllProjects(QJsonObject&);

    /*!  @input: single mappable project object with id: QJsonObject&
     *    @desc: retreives a projects from the database by id and builds
     *           a maps to represent the objects returned
     *  @output: status: bool (success or failure)
     */
    bool retrieveProjectUsingID(QJsonObject&);

    /*!  @input: single user mappable object with id: QJsonObject&
     *    @desc: retreives projects from the database that is associated to
     *           this user and builds a maps to represent the objects returned
     *  @output: status: bool (success or failure)
     */
    bool retrieveProjectsForUser(QJsonObject&);

    /*!  @input: single project mappable object with id: QJsonObject&
     *    @desc: retreives all PPPs registered to this project from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: bool (success or failure)
     */
    bool retrievePPPsForProject(QJsonObject&);

    /*!  @input: single object with username: QJsonObject&
     *    @desc: retreives all PPPs registered to this project from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: bool (success or failure)
     */
    bool retrieveUserWithUsername(QJsonObject&);

    /*!  @input: single mappable user object: QJsonObject&
     *    @desc: retreives the user's PPPs from the database
     *           and builds a maps to represent the objects returned
     *  @output: status: bool (success or failure)
     */
    bool retrievePPPForUser(QJsonObject&);

    /*!
     *  Data Storage Services
     */

    /*!   @input: a mappable user and PPP object: QJsonObject&
     *    @desc: saves the new PPP for the user into the database
     *  @output: status: bool (success or failure)
     */
    bool userCreatedPPP(QJsonObject&);

    /*!  @input: a mappable user and PPP object: QJsonObject&
     *    @desc: updates the existing PPP for the user into the database
     *  @output: status: bool (success or failure)
     */
    bool userUpdatedPPP(QJsonObject&);

    /*!  @input: a mappable user and PPP object: QJsonObject&
     *    @desc: deletes the PPP for the user into the database
     *  @output: status: bool (success or failure)
     */
    bool userDeletedPPP(QJsonObject&);

    /*!  @input: a mappable user object: QJsonObject&
     *    @desc: saves the new user into the database
     *  @output: status: bool (success or failure)
     */
    bool createUser(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: saves the new project for the user into the database
     *  @output: status: bool (success or failure)
     */
    bool userCreatedProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: updates the existing project for the user into the database
     *  @output: status: bool (success or failure)
     */
    bool userUpdatedProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: registered user into the project saves the record into the database
     *  @output: status: bool (success or failure)
     */
    bool userRegisteredInProject(QJsonObject&);

    /*!  @input: a mappable user and project object: QJsonObject&
     *    @desc: unregistered user from the project saves the record into the database
     *  @output: status: bool (success or failure)
     */
    bool userUnRegisteredInProject(QJsonObject&);

private:

    /*!  @input: a JSON request object: QJsonObject&
     *    @desc: cleares the JSON object of all its key value mappings
     *  @output: n/a: void
     */
    void clearJsonObject(QJsonObject&);

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
};

#endif // DATAACCESSDISPATCHER_H
