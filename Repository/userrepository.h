#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QVector>
#include "irepository.h"

class User;

class UserRepository : public IRepository<User>
{
public:
    UserRepository();
    ~UserRepository();

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

};

#endif // USERREPOSITORY_H
