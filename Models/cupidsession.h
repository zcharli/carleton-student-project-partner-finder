#ifndef CUPIDSESSION_H
#define CUPIDSESSION_H

#include "user.h"
#include "projectpartnerprofile.h"
#include "project.h"

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
     *       @param: currentUser:
     *        @desc: sets the current project for session
     *      @return: void
     */
    void setCurrentProject(Project*);

    /*!
     *       @param: currentUser:
     *        @desc: sets the current profile for session
     *      @return: void
     */
    void setCurrentProfile(ProjectPartnerProfile*);

    /*!
     *       @param: none
     *        @desc: free the current user from memory, ready to add a new user.
     *      @return: void
     */
    void deleteCurrentUser();

    /*!
     *       @param: none
     *        @desc: free the current project from memory, ready to add a new project.
     *      @return: void
     */
    void deleteCurrentProject();

    /*!
     *       @param: none
     *        @desc: free the current profile from memory, ready to add a new ppp.
     *      @return: void
     */
    void deleteCurrentProfile();

    /*!
     *       @param: none
     *        @desc: returns the current user that is logged in
     *      @return: currentUser pointer: User*
     */
    User* getCurrentUser();

    /*!
     *       @param: none
     *        @desc: returns the current project that is in the session
     *      @return: currentUser pointer: User*
     */
    Project* getCurrentProject();

    /*!
     *       @param: none
     *        @desc: returns the current profile that is in the session
     *      @return: currentUser pointer: User*
     */
    ProjectPartnerProfile* getCurrentProfile();

    ~CupidSession();

private:
  CupidSession();
  static CupidSession *singleton;
  User* currentUser;
  ProjectPartnerProfile* currentPPP;
  Project* currentProject;

};

#endif // CUPIDSESSION_H
