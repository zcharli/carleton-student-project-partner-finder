#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QVector>
#include <QtSql/QSqlDatabase>
#include "irepository.h"

class User;
class ProjectPartnerProfile;

class UserRepository : public IRepository<User>
{
public:
    UserRepository();
    virtual ~UserRepository();

    /*!
     *       @param: objectToSave: User&
     *        @desc: saves the type User to database,
     *               when User.id is 0 or null:
     *                   insert -> returns ID of the new row
     *                   else update
     *      @return: saveSuccessful: int
     */
    virtual unsigned int save(const User&);

    /*!
     *       @param: idToDelete: int
     *        @desc: deletes the type User to database
     *      @return: success or failure: int
     */
    virtual unsigned int deleteFromRepo(const int);

    /*!
     *       @param: idToFetch: int
     *        @desc: fetchs the type User to database
     *      @return: entityObject: TEntity&
     */
    virtual User& fetchById(const int);

    /*!
     *       @param: idToFetch (optional): int
     *        @desc: fetchs all type User to database
     *      @return: entityObject: QVector<User*>&
     */
    virtual QVector<User*>& fetchAll(const int=0);

    /*!
     *       @param: userName: QString
     *        @desc: fetchs the user object from database
     *      @return: success or failure: bool
     *        @note: checks if username is associated with admin/student user
     */
    bool validateLogin(const QString&);

    /*!
     *       @param: user: User&, ppp: ProjectPartnerProfile&
     *        @desc: handles the database actions necessary when a user creates a ppp
     *      @return: success or failure: bool
     */
    int userCreatedPPP(User&, ProjectPartnerProfile&);

    /*!
     *       @param: user: User&, ppp: ProjectPartnerProfile&
     *        @desc: handles the database actions necessary for retrieving the PPP for a User
     *      @return: success or failure: bool
     */
    int fetchPPPForUser(User&, ProjectPartnerProfile&);

    /*!
     *       @param: user: User&, ppp: ProjectPartnerProfile&
     *        @desc: handles the database actions necessary for when a user updates his/her ppp
     *      @return: success or failure: bool
     */
    int userUpdatedPPP(User&, ProjectPartnerProfile&);

    /*!
     *       @param: user: User&, ppp: ProjectPartnerProfile&
     *        @desc: handles the database actions necessary for when the user has deleted his/her ppp
     *      @return: success or failure: bool
     */
    int userDeletedPPP(User&, ProjectPartnerProfile&);

private:
    QSqlDatabase db;

};

#endif // USERREPOSITORY_H
