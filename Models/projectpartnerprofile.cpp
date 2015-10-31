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
    Qualification::GetWorkEthicBitForWorkEthicQualification(bitPosition, qualifications[userWorkEthic]);
}




