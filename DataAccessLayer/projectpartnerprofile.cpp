#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"
#include <QJsonArray>
#include "mapconfigs.h"

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser,int pscore,int tscore,unsigned char we, Qualification* qualifications) :
    user(studentUser), personalTechnicalScore(pscore), teammateTechnicalScore(tscore), workEthic(we)
{
    this->qualifications = qualifications;
    pppID = 0;
}

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser, const QJsonObject& pppJSON) :
    user(studentUser)
{
    deserializeJSONFromRetrieve(pppJSON);
}

ProjectPartnerProfile::~ProjectPartnerProfile()
{
    user.profile = NULL;
    delete[] qualifications;
    qualifications = NULL;
    // Added deleting users since we allocated this when populating
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

bool ProjectPartnerProfile::serializeJSONForSave(QJsonObject&)
{
    return false;
}


bool ProjectPartnerProfile::deserializeJSONFromRetrieve(const QJsonObject&)
{
    return false;
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
