#include "studentuser.h"
#include "projectpartnerprofile.h"
#include "project.h"
#include "mapconfigs.h"
#include "dataaccessfacade.h"

StudentUser::StudentUser(QString& fName, QString& lName, QString& userName):
    User(fName, lName, userName)
{
    profile = NULL;
    userType = Student;
    pppIDForFetch = 0;
}

StudentUser::StudentUser(const StudentUser& copy):
    User(copy.firstName, copy.lastName, copy.userName)
{
    profile = NULL;
    userType = Student;
    pppIDForFetch = copy.pppIDForFetch;
}

StudentUser::StudentUser(const QJsonObject& studentJSON)
{
    profile = NULL;
    userType = Student;
    pppIDForFetch = 0;
    deserializeJSONFromRetrieve(studentJSON);
}

StudentUser::~StudentUser()
{
    if(profile != NULL)
    {
        DataAccessFacade::doneUsingProfile(profile);
        profile = NULL;
    }
}

void StudentUser::setFetchIDForPPP(int fetchID)
{
    pppIDForFetch = fetchID;
}

int StudentUser::getFetchIDForPPP()
{
    return pppIDForFetch;
}

ProjectPartnerProfile* StudentUser::getProfile()
{
    if(profile == NULL)
    {
        return NULL;
    }
    return profile;
}

void StudentUser::setProfile(ProjectPartnerProfile* newProfile)
{

   profile = newProfile;
}

bool StudentUser::serializeJSONForSave(QJsonObject& userJSON)
{
    int i;
    if(id != 0)
    {
        userJSON[USER_id] = id;
    }

    if(pppIDForFetch != 0)
    {
        userJSON[STUDENT_pppIDForFetch] = pppIDForFetch;
    }

    userJSON[USER_firstName] = firstName;
    userJSON[USER_lastName] = lastName;
    userJSON[USER_userName] = userName;
    userJSON[USER_userType] = (int)userType;

    /*if(profile != NULL)
    {
        QJsonObject pppJSON;
        profile->serializeJSONForSave(pppJSON);
        userJSON[STUDENT_ppp] = pppJSON;
    }
    */
    return true;
}


bool StudentUser::deserializeJSONFromRetrieve(const QJsonObject& userJSON)
{
    int i;
    id = userJSON[USER_id].toInt();
    firstName = userJSON[USER_firstName].toString();
    lastName = userJSON[USER_lastName].toString();
    userName = userJSON[USER_userName].toString();

    userType = (UserType)userJSON[USER_userType].toInt();
    if(userJSON.contains(STUDENT_pppIDForFetch))
    {
        pppIDForFetch = userJSON[STUDENT_pppIDForFetch].toInt();
    }

    /*if(userJSON.contains(STUDENT_ppp))
    {
       // Note that this call to the
       if(profile == NULL)
       {
            profile = DataAccessFacade::defaultProfile(*this);
           //profile = new ProjectPartnerProfile(*this);
       }
       QJsonObject ppp = userJSON[STUDENT_ppp].toObject();
       profile->deserializeJSONFromRetrieve(ppp);
    }*/

    return true;
}
