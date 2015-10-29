#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QVector>
#include <QtSql/QSqlDatabase>

class User;
class ProjectPartnerProfile;

class UserRepository
{
public:
    UserRepository(QSqlDatabase&);
    ~UserRepository();

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

    /*!
     *       @param: username: QString&, user: User&
     *        @desc: handles the database actions necessary for when a user attempts to login
     *      @return: success or failure: bool
     */
    int retrieveUserWithUsername(QString& username, User& user);

    /*!
     *       @param: user: User&
     *        @desc: handles the database actions necessary for when a user creates a new Account
     *      @return: success or failure: bool
     */
    int createUser(User& user);


private:
    QSqlDatabase db;

};

#endif // USERREPOSITORY_H
