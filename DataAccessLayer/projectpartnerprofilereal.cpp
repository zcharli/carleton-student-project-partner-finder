#include "projectpartnerprofilereal.h"

ProjectPartnerProfileReal::ProjectPartnerProfileReal(StudentUser& user, int pscore, int tscore, unsigned char we, Qualification* qualifications):
ProjectPartnerProfile(user, pscore, tscore, we, qualifications)
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
