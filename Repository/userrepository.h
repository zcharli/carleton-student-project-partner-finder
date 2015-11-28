#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QtSql/QSqlDatabase>
#include <QJsonObject>

class UserRepository
{
public:
    UserRepository(QSqlDatabase&);
    ~UserRepository();

    /*!
     *       @param: user: QJsonObject&, userId: int
     *        @desc: handles the database actions necessary when a user creates a ppp
     *      @return: success or failure: bool
     */
    int userCreatedPPP(QJsonObject& user, int userId);

    /*!
     *       @param: user: QJsonObject&, user id: int
     *        @desc: handles the database actions necessary for retrieving the PPP for a User
     *      @return: success or failure: bool
     */
    int fetchPPPForUser(QJsonObject&, int);

    /*!
     *       @param: user: QJsonObject&
     *        @desc: handles the database actions necessary for when a user updates his/her ppp
     *      @return: success or failure: bool
     */
    int userUpdatedPPP(QJsonObject& user);

    /*!
     *       @param: userId: int
     *        @desc: handles the database actions necessary for when the user has deleted his/her ppp
     *      @return: success or failure: bool
     */
    int userDeletedPPP(int userId);

    /*!
     *       @param: user: QJsonObject&, user, username: QString&, type: int
     *        @desc: handles the database actions necessary for when a user attempts to login
     *      @return: success or failure: bool
     */
    int retrieveUserWithUsername(QJsonObject& user, QString& username, int type);

    /*!
     *       @param: user: QJsonObject&
     *        @desc: handles the database actions necessary for when a user creates a new Account
     *      @return: success or failure: bool
     */
    int createUser(QJsonObject& user);

private:
    QSqlDatabase db;

};

#endif // USERREPOSITORY_H
