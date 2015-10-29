#ifndef CUPIDSESSION_H
#define CUPIDSESSION_H

#include "user.h"

class CupidSession
{
public:

    /*!
     *       @param: none
     *        @desc: returns the singleton isntance of cupid session
     *      @return: void
     */
    static CupidSession* getInstance();

    /*!
     *       @param: currentUser:
     *        @desc: sets the current user for session
     *      @return: void
     */
    void setCurrentUser(User*);

    /*!
     *       @param: none
     *        @desc: free the current user from memory, ready to add a new user.
     *      @return: void
     */
    void deleteCurrentUser();

    /*!
     *       @param: none
     *        @desc: returns the current user that is logged in
     *      @return: currentUser pointer: User*
     */
    User* getCurrentUser();
    ~CupidSession();

private:
  CupidSession() {};
  static CupidSession *singleton;
  User* currentUser;

};

#endif // CUPIDSESSION_H
