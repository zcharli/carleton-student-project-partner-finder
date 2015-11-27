#include "studentuser.h"
#include "projectpartnerprofile.h"
#include "project.h"

StudentUser::StudentUser(QString& fName, QString& lName, QString& userName, int id):
    User(fName, lName, userName, id)
{
    profile = NULL;
    userType = Student;
    pppIDForFetch = 0;
}

StudentUser::~StudentUser()
{
    if(profile != NULL)
    {
        delete profile;
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
    if(profile == NULL)
    {
        profile = newProfile;
    }
    else
    {
        delete profile;
        profile = newProfile;
    }
}

bool StudentUser::serializeJSONForSave(QJsonObject& userJSON)
{
    int i;
    if(id != 0)
    {
        userJSON["id"] = id;
    }

    if(pppIDForFetch != 0)
    {
        userJSON["pppIDForFetch"] = pppIDForFetch;
    }

    userJSON["firstName"] = firstName;
    userJSON["lastName"] = lastName;
    userJSON["userName"] = userName;
    userJSON["userType"] = (int)userType;

    if(profile != NULL)
    {
        QJsonObject pppJSON;
        userJSON["ppp"] = profile->serializeJSONForSave(pppJSON);
    }

    return true;
}


bool StudentUser::deserializeJSONFromRetrieve(const QJsonObject& userJSON)
{
    int i;
    id = userJSON["id"].toInt();
    firstName = userJSON["firstName"].toString();
    lastName = userJSON["lastName"].toString();
    userName = userJSON["userName"].toString();
    userType = (UserType)userJSON["userType"].toInt();
    if(userJSON.contains("pppIDForFetch"))
    {
        pppIDForFetch = userJSON["pppIDForFetch"].toInt();
    }

    if(userJSON.contains("ppp"))
    {
        // Note that this call to the
        QJsonObject ppp = userJSON["ppp"].toObject();
        profile->deserializeJSONFromRetrieve(ppp);
    }
    return true;
}
