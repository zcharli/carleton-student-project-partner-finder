#ifndef STUDENTUSER_H
#define STUDENTUSER_H

#include "user.h"

#include <QVector>

//forward declarations
class ProjectPartnerProfile;
class Project;


class StudentUser : public User
{

    friend class ProjectPartnerProfile;
    ProjectPartnerProfile *profile;
    //Keep track of if the StudentUser currently has a ppp
    int pppIDForFetch;

public:
    StudentUser(QString&, QString&, QString&, int);
    virtual ~StudentUser();

    //accessor functions
    /*!
     *       @param: none
     *        @desc: gets the ProjectPartnerProfile Associated with the StudentUser
     *      @return: studentUserPPP: ProjectPartnerProfile&
     */
    ProjectPartnerProfile* getProfile();


    /*!
     *       @param: pppID of the StudentUser if he/she has one
     *        @desc: sets the PPPID of the user if he/she has one. This will aid in subsequent fetch queries to the db
     *      @return: void
     */
    void setFetchIDForPPP(int);

    /*!
     *       @param: none
     *        @desc: gets the PPPID of the user if he/she has one. This will aid in subsequent fetch queries to the db
     *      @return: fetchIDForUsersPPP: int
     */
    int getFetchIDForPPP();
};

#endif // STUDENTUSER_H
