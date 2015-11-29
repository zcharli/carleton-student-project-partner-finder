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
    friend class ProjectPartnerProfileProxy;
    friend class ProjectPartnerProfileReal;
    ProjectPartnerProfile *profile;
    //Keep track of if the StudentUser currently has a ppp
    int pppIDForFetch;

public:
    StudentUser(const QJsonObject&);
    StudentUser(QString&, QString&, QString&);

    virtual ~StudentUser();

    //accessor functions
    /*!
     *       @param: none
     *        @desc: gets the ProjectPartnerProfile Associated with the StudentUser
     *      @return: studentUserPPP: ProjectPartnerProfile&
     */
    ProjectPartnerProfile* getProfile();

    /*!
     *       @param: none
     *        @desc: sets the ProjectPartnerProfile Associated with the StudentUser
     *      @return: studentUserPPP: ProjectPartnerProfile&
     */
    void setProfile(ProjectPartnerProfile*);


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

    /*!
     *       @param: empty Json Object: QJsonObject&
     *        @desc: serializes the object implementing into JSON
     *      @return: success or failure: bool
     */
    virtual bool serializeJSONForSave(QJsonObject&);

    /*!
     *       @param: objectToDeSerialize: QJsonObject&
     *        @desc: deserializes the the JSON object to create the object back
     *      @return: success or failure: bool
     */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&);

};

#endif // STUDENTUSER_H
