#ifndef PROJECT_H
#define PROJECT_H

#include "configuration.h"

#include <QVector>
#include <QString>
#include <QSet>
#include <QList>
#include "imappable.h"

//forward declarations
class Configuration;
class ProjectPartnerProfile;
class QJsonObject;

class Project : private IMappable
{
    Configuration *projectConfigurations;
    QSet<ProjectPartnerProfile> registeredPPPs;
    int numberOfRegisteredUsers;
    QString title;
    QString description;
    int id;

public:
    Project(const QJsonObject&);
    Project(QString, QString);
    virtual ~Project();

    //accessor Functions
    /*!
     *       @param: configuration: ConfigurationType
     *        @desc: get the configuration for the specifed index (to match configuration type)
     *      @return: configuration: Configuration
     */
    Configuration getProjectConfiguration(int);

    /*!
     *       @param: configuration: Configuration*
     *        @desc: set the configurations that the AdministratorUser has entered
     *      @return: none
     */
    void changeConfiguration(Configuration);

    /*!
     *       @param: none
     *        @desc: get the number of registered users
     *      @return: numUsersRegisted: int
     */
    int getNumberOfRegisteredUsers();

    /*!
     *       @param: newNum: int
     *        @desc: sets the number of registered users
     *      @return: void
     */
    void setNumberOfRegisteredUsers(int);

    /*!
     *       @param: profileToRegister: ProjectPartnerProfile&
     *        @desc: register the given PPP to the project
     *               Must call isPPPRegistered first to check if the
     *               Profile has already been registered to prevent duplication
     *      @return: void
     */
    void registerPPP(ProjectPartnerProfile&);

    /*!
     *       @param: pppList: QVector<ProjectPartnerProfile*>&
     *        @desc: returns the list of PPPs that are registered into the project
     *      @return: void
     */
    QList<ProjectPartnerProfile> getRegisteredPPPs();

    /*!
     *       @param: profileToUnregister: ProjectPartnerProfile&
     *        @desc: unregister the given PPP from the project
     *               (if the PPP is registered). Does nothing otherwise.
     *      @return: void
     */
    void unRegisterPPP(ProjectPartnerProfile&);

    /*!
     *       @param: profileToCheck: ProjectPartnerProfile&
     *        @desc: check if the given PPP is registered in the project;
     *      @return: isPPPRegistered: bool
     */
    bool isPPPRegistered(ProjectPartnerProfile&);

    /*!
     *       @param: none
     *        @desc: gets the title of the project
     *      @return: title: QString&
     */
    QString& getTitle();

    /*!
     *       @param: none
     *        @desc: gets the description of the project
     *      @return: description: QString&
     */
    QString& getDescription();

    /*!
     *       @param: newTitle: QString&
     *        @desc: sets the title of the project
     *      @return: void
     */
    void setTitle(QString&);

    /*!
     *       @param: newDescription: QString&
     *        @desc: sets the description of the project
     *      @return: void
     */
    void setDescription(QString&);

    /*!
     *       @param: newId: int
     *        @desc: sets the id of the project after its been added to db
     *      @return: void
     */
    void setProjectId(int);

    /*!
     *       @param: none
     *        @desc: gets the id of the project after its been added to db
     *      @return: id: int
     */
    int getProjectId();

    /*!
     *       @param: ppp: ProjectPartnerProfile*
     *        @desc: adds the ppp to the collection of profiles for this project
     *      @return: none
     */
    void addPPPtoProject(ProjectPartnerProfile&);

    /*!
     *       @param: empty Json Object: QJsonObject&
     *        @desc: serializes the object implementing into JSON
     *      @return: success or failure: bool
     */
    virtual bool serializeJSONForSave(QJsonObject&);

    /*!
     *       @param: objectToDeSerialize: QJsonObject&
     *        @desc: deserializes the JSON object to create the object back
     *      @return: success or failure: bool
     */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&);

    /*!
     *       @param: Json objectToSerialize: QJsonObject&, projectList: QVector<Project&>&
     *        @desc: serializes the list of projects into a JSON object
     *      @return: success or failure: bool
     */
    static bool serializeJSONFromCollection(QJsonObject&, const QVector<Project*>&);

    /*!
     *       @param: Json objectToDeSerialize: QJsonObject&, projectList to fill: QVector<Project&>&
     *        @desc: deserializes JSON object into a list of projects
     *      @return: success or failure: bool
     */
    static bool deserializeJSONFromCollection(const QJsonObject&, QVector<Project*>&);

};

#endif // PROJECT_H
