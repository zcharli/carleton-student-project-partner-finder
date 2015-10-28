#ifndef ADMINISTRATORUSER_H
#define ADMINISTRATORUSER_H

#include <QVector>
#include "user.h"

//forward declarations
class Project;

class AdministratorUser : public User
{
    QVector<Project*> projectsCreated;

public:
    AdministratorUser(QString&, QString&, QString&, int);
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
     *       @param: projectToCheck: Project*
     *        @desc: checks if the AdministratorUser is the owner of a given Project
     *               returns true if AdministratorUser is the owner. False otherwise
     *      @return: didCreate: bool
     */
    bool didCreateProject(Project*);
};

#endif // ADMINISTRATORUSER_H
