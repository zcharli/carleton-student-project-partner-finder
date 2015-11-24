#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"

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
{}

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
