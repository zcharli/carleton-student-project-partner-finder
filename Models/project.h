#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>
#include <QString>
#include "configuration.h"

//forward declarations
class Configuration;
class ProjectPartnerProfile;

class Project
{
    Configuration *projectConfigurations;
    QVector<ProjectPartnerProfile*> registeredPPPs;
    int numberOfRegisteredUsers;
    QString title;
    QString description;

public:
    Project(QString&, QString&);
    ~Project();

    //accessor Functions
    /*!
     *       @param: configuration: ConfigurationType
     *        @desc: get the configuration for the specifed index (to match configuration type)
     *      @return: configuration: Configuration
     */
    Configuration getProjectConfiguration(int);

    /*!
     *       @param: newConfiguration: Configuration
     *        @desc: get the configurations set by the AdministratorUser on the project
     *      @return: void
     */
    void changeConfiguration(Configuration);
    \
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
     *       @param: profileToRegister: ProjectPartnerProfile*
     *        @desc: register the given PPP to the project
     *               Must call isPPPRegistered first to check if the
     *               Profile has already been registered to prevent duplication
     *      @return: void
     */
    void registerPPP(ProjectPartnerProfile*);

    /*!
     *       @param: profileToUnregister: ProjectPartnerProfile*
     *        @desc: unregister the given PPP from the project
     *               (if the PPP is registered). Does nothing otherwise.
     *      @return: void
     */
    void unRegisterPPP(ProjectPartnerProfile*);

    /*!
     *       @param: profileToCheck: ProjectPartnerProfile*
     *        @desc: check if the given PPP is registered in the project;
     *      @return: isPPPRegistered: bool
     */
    bool isPPPRegistered(ProjectPartnerProfile* profile);

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
};

#endif // PROJECT_H
