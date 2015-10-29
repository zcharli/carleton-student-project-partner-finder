#ifndef STUDENTUSER_H
#define STUDENTUSER_H

#include <QVector>
#include "user.h"

//forward declarations
class ProjectPartnerProfile;
class Project;


class StudentUser : public User
{

    ProjectPartnerProfile *profile;
    QVector<Project*> registeredProjects;
    int numProjectsRegistered;

public:
    StudentUser(QString&, QString&, QString&, int);
    virtual ~StudentUser();

    //accessor functions
    /*!
     *       @param: none
     *        @desc: get the number of projects StudentUser is registered in
     *      @return: number of projects registered in : int
     */
    int getNumberOfProjectsRegistered();

    /*!
     *       @param: newNum: int
     *        @desc: sets the number of projects StudentUser is registered in
     *      @return: void
     */
    void setNumberOfProjectsRegistered(int);

    /*!
     *       @param: projectToAdd: Project*
     *        @desc: adds the given project to the list of registered projects for the StudentUser
     *      @return: void
     */
    void addProjectToRegisteredProjects(Project*);

    /*!
     *       @param: projectToRemove: Project*
     *        @desc: removes the given project from the list of registered projects for the StudentUser
     *               (if the project is contained in the list). Does nothing otherwise
     *      @return: void
     */
    void removeProjectFromRegisteredProjects(Project*);

    /*!
     *       @param: projectToCheck: Project*
     *        @desc: checks if the StudentUser is currently registered in a given Project
     *               returns true if StudentUser is registered. False otherwise
     *      @return: isRegistered: bool
     */
    bool isRegisteredInProject(Project*);

    /*!
     *       @param: none
     *        @desc: gets the ProjectPartnerProfile Associated with the StudentUser
     *      @return: studentUserPPP: ProjectPartnerProfile&
     */
    ProjectPartnerProfile* getProfile();
};

#endif // STUDENTUSER_H
