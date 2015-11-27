#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"
#include <QJsonArray>
ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser):
    user(studentUser)
{
    if(studentUser.profile)
    {
        delete studentUser.profile;
        studentUser.profile = NULL;
    }
    studentUser.profile = this;
    qualifications = Qualification::DefaultQualifications();
    pppID = 0;
}

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser,int pscore,int tscore,char we) :
    user(studentUser), personalTechnicalScore(pscore), teammateTechnicalScore(tscore), workEthic(we)
{
    qualifications = Qualification::DefaultQualifications();
}

ProjectPartnerProfile::~ProjectPartnerProfile()
{
    user.profile = NULL;
    delete qualifications;
    qualifications = NULL;
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

void ProjectPartnerProfile::changeQualification(Qualification newQualification)
{
    qualifications[newQualification.getType()] = newQualification;
}

Qualification ProjectPartnerProfile::getQualification(int index)
{
    //TODO: Need to do error checking here.
    return qualifications[index];
}

bool ProjectPartnerProfile::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    if(!Qualification::GetWorkEthicBitForWorkEthicQualification(bitPosition, qualifications[userWorkEthic]))
    {
        return false;
    }
    return true;
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


char ProjectPartnerProfile::getWorkEthicByte()
{
    return workEthic;
}

void ProjectPartnerProfile::setWorkEthicByte(char meThic)
{
    workEthic = meThic;
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

    QJsonArray qualificationsArray;

    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
       QJsonObject qualification;
       qualifications[i].serializeJSONForSave(qualification);
       qualificationsArray.append(qualification);
    }

    pppJSON["qualifications"] = qualificationsArray;

    return true;
}


bool ProjectPartnerProfile::deserializeJSONFromRetrieve(const QJsonObject& pppJSON)
{
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
