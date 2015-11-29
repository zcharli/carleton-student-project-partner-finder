#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"
#include <QJsonArray>

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser,int pscore,int tscore,unsigned char we, Qualification* qualifications) :
    user(studentUser), personalTechnicalScore(pscore), teammateTechnicalScore(tscore), workEthic(we)
{
    this->qualifications = qualifications;
    pppID = 0;
}

ProjectPartnerProfile::~ProjectPartnerProfile()
{
    user.profile = NULL;
    delete[] qualifications;
    qualifications = NULL;
}

void ProjectPartnerProfile::changeQualification(Qualification qualification)
{
    // subclasses must implement this
    return;
}

Qualification ProjectPartnerProfile::getQualification(int)
{
    // subclasses must implement this
    return noneType;
}

bool ProjectPartnerProfile::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    //  Subclasses must implement this
    return false;
}

void ProjectPartnerProfile::updateProfileScores()
{
    //Subclasses must implement this function
}

StudentUser& ProjectPartnerProfile::getStudentUser()
{
    return user;
}

int ProjectPartnerProfile::getPPPID()
{
    return pppID;
}

int ProjectPartnerProfile::getPPPID() const
{
    return pppID;
}

void ProjectPartnerProfile::setPPPID(int id)
{
    this->pppID = id;
}

unsigned char ProjectPartnerProfile::getWorkEthicByte()
{
    return workEthic;
}

void ProjectPartnerProfile::setWorkEthicByte(unsigned char meThic)
{
    workEthic = meThic;
}

int ProjectPartnerProfile::getPersonalTechnicalScore()
{
    return personalTechnicalScore;
}

void ProjectPartnerProfile::setPersonalTechnicalScore(int iScore)
{
    personalTechnicalScore = iScore;
}

int ProjectPartnerProfile::getTeammateTechnicalScore()
{
    return teammateTechnicalScore;
}

void ProjectPartnerProfile::setTeammateTechnicalScore(int tScore)
{
    teammateTechnicalScore = tScore;
}

bool ProjectPartnerProfile::serializeJSONForSave(QJsonObject& pppJSON)
{
    int i;
    if(pppID != 0)
    {
        pppJSON["pppID"] = pppID;
    }

    pppJSON["personalTechnicalScore"] = personalTechnicalScore;
    pppJSON["teammateTechnicalScore"] = teammateTechnicalScore;
    pppJSON["workEthic"] = workEthic;

    if(qualifications != NULL)
    {
        QJsonArray qualificationsArray;

        for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
        {
            QJsonObject qualification;
            qualifications[i].serializeJSONForSave(qualification);
            qualificationsArray.append(qualification);
        }

        pppJSON["qualifications"] = qualificationsArray;
    }

    return true;
}

bool ProjectPartnerProfile::deserializeJSONFromRetrieve(const QJsonObject& pppJSON)
{
    // There are some cases where perosnal and teammate tech scores are NOT
    // pulled in for the logged in user
    // tech score are pulled in for when the algorithm needs them
    int i;
    pppID = pppJSON["pppID"].toInt();
    if(pppJSON.contains("personalTechnicalScore"))
    {
        personalTechnicalScore = pppJSON["personalTechnicalScore"].toInt();
        teammateTechnicalScore = pppJSON["teammateTechnicalScore"].toInt();
        workEthic = (char)pppJSON[""].toInt();
    }

    if(pppJSON.contains("qualifications"))
    {
        QJsonArray qualificationsArray = pppJSON["qualifications"].toArray();
        for(i=0;i<qualificationsArray.size();++i)
        {
            QJsonObject qualification = qualificationsArray[i].toObject();
            qualifications[i].deserializeJSONFromRetrieve(qualification);
        }
    }

    return true;
}
