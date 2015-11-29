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
    delete qualifications;
    qualifications = NULL;
    // Added deleting users since we allocated this when populating
}

void ProjectPartnerProfile::changeQualification(Qualification qualification)
{
    return;
}

Qualification ProjectPartnerProfile::getQualification(int)
{
    return noneType;
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

bool ProjectPartnerProfile::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    if(!Qualification::GetWorkEthicBitForWorkEthicQualification(bitPosition, qualifications[userWorkEthic]))
    {
        return false;
    }
    return true;
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


void ProjectPartnerProfile::updateProfileScores()
{
    float teamScore;
    float personalScore;

    Qualification::TechnicalScoreForProfile(*this, personalScore, teamScore);

}


bool ProjectPartnerProfile::serializeJSONForSave(QJsonObject&)
{
    return false;
}


bool ProjectPartnerProfile::deserializeJSONFromRetrieve(const QJsonObject&)
{
    return false;
}
