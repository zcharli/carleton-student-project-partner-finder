#ifndef PROJECTREPOSITORY_H
#define PROJECTREPOSITORY_H

#include <QVector>
#include "irepository.h"

class Project;

class ProjectRepository : public IRepository<Project>
{
public:
    ProjectRepository();
    ~ProjectRepository();

    /*!
     *       @param: objectToSave: Project&
     *        @desc: saves the type Project to database,
     *               when Project.id is 0 or null:
     *                   insert -> returns ID of the new row
     *                   else update
     *      @return: saveSuccessful: int
     */
    virtual unsigned int save(const Project&);

    /*!
     *       @param: idToDelete: int
     *        @desc: deletes the type Project to database
     *      @return: success or failure: int
     */
    virtual unsigned int deleteFromRepo(const int);

    /*!
     *       @param: idToFetch: int
     *        @desc: fetchs the type Project to database
     *      @return: entityObject: TEntity&
     */
    virtual Project& fetchById(const int);

    /*!
     *       @param: idToFetch (optional): int
     *        @desc: fetchs all type Project to database
     *      @return: entityObject: QVector<Project*>&
     */
    virtual QVector<Project*>& fetchAll(const int=0);

    /*!
     *       @param: idToRegister, idOfProject: int. int
     *        @desc: registers the user id to project
     *      @return: success or failure error code: int
     */
    unsigned int registerPPPToProject(const int,const int);

    /*!
     *       @param: idToUnRegister, idOfProject: int. int
     *        @desc: unregisteres the user id to project
     *      @return: success or failure error code: int
     */
    unsigned int unRegisterPPPFromProject(const int, const int);

// It is possible we don't be needing this
//    /*!
//     *       @param: none
//     *        @desc: get the configurations set by the AdministratorUser on the project
//     *      @return: configurations: QVector<Configuration*>*
//     *        @note: this repository class fetchs pointers and should be coverted to
//     *               references when passed to the project class (getProjectConfigurations)
//     *               in project.h
//     */
//    QVector<Configuration*>* fetchProjectConfigurations();



private:
    //const ProjectConfigurationRepository& configurationRepo; // May not need this
};

#endif // PROJECTREPOSITORY_H
