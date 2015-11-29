#include "projectpartnerprofilereal.h"

ProjectPartnerProfileReal::ProjectPartnerProfileReal(StudentUser& user, int pscore, int tscore, unsigned char we, Qualification* qualifications):
ProjectPartnerProfile(user, pscore, tscore, we, qualifications)
{
}

ProjectPartnerProfileReal::~ProjectPartnerProfileReal()
{
}

void ProjectPartnerProfileReal::changeQualification(Qualification newQualification)
{
    qualifications[newQualification.getType()] = newQualification;
}

Qualification ProjectPartnerProfileReal::getQualification(int index)
{
    //TODO: Need to do error checking here.
    return qualifications[index];
}

bool ProjectPartnerProfileReal::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    if(!Qualification::GetWorkEthicBitForWorkEthicQualification(bitPosition, qualifications[userWorkEthic]))
    {
        return false;
    }
    return true;
}

void ProjectPartnerProfileReal::updateProfileScores()
{
    float teamScore;
    float personalScore;

    Qualification::TechnicalScoreForProfile(*this, personalScore, teamScore);
    personalTechnicalScore = personalScore;
    teammateTechnicalScore = teamScore;
    workEthic = (unsigned char)(this->qualifications[userWorkEthic].getValue());

    //TODO: technical normalizations for profile
}
