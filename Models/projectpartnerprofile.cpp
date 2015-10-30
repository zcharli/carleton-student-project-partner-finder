#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser, QString& bio, Qualification* qualifications):
    user(studentUser), biography(bio)
{
    this->qualifications = qualifications;
}

ProjectPartnerProfile::~ProjectPartnerProfile()
{}

QString& ProjectPartnerProfile::getBiography()
{
    return biography;
}
void ProjectPartnerProfile::setBiography(QString& newBiography)
{
    biography = newBiography;
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
    char workEthicBit = char(qualifications[userWorkEthic].getValue());
    //get the value of the work ethic bit
    return (workEthicBit & (1 << bitPosition)) >> bitPosition;
}




