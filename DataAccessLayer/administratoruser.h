#ifndef ADMINISTRATORUSER_H
#define ADMINISTRATORUSER_H

#include "user.h"

#include <QVector>

//forward declarations
class Project;
class QJsonObject;

class AdministratorUser : public User
{

public:
    AdministratorUser(QString&, QString&, QString&);
    AdministratorUser(const QJsonObject&);
    virtual ~AdministratorUser();

    //accessor functions
    /*!
     *       @param: none
     *        @desc: get the number of projects AdministratorUser has
     *      @return: number of projects created: int
     */
    int getNumberOfProjectsCreated();

    /*!
     *       @param: projectToAdd: Project*
     *        @desc: adds the given project to the list of projects created by the AdministratorUser
     *      @return: void
     */
    void addProjectToCreatedProjects(Project*);

    /*!
     *       @param: projectToRemove: Project*
     *        @desc: removes the given project from the list of projects created by the AdministratorUser
     *               (if the project is contained in the list). Does nothing otherwise
     *      @return: void
     */
    void removeProjectFromCreatedProjects(Project*);

    /*!
     *       @param: empty Json Object: QJsonObject&
     *        @desc: serializes the object implementing into JSON
     *      @return: success or failure: bool
     */
    virtual bool serializeJSONForSave(QJsonObject&);

    /*!
     *       @param: objectToDeSerialize: QJsonObject&
     *        @desc: deserializes the the JSON object to create the object back
     *      @return: success or failure: bool
     */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&);

};

#endif // ADMINISTRATORUSER_H
