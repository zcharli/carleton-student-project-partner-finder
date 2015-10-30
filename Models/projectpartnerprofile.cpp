#include "projectpartnerprofile.h"
#include "studentuser.h"
#include "qualification.h"

ProjectPartnerProfile::ProjectPartnerProfile(StudentUser& studentUser, QString& bio):
    user(studentUser), biography(bio)
{
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

void ProjectPartnerProfile::addQualificationToPersonalQualifications(Qualification qualification)
{
    personalQualifications.append(qualification);
}

void ProjectPartnerProfile::addQualificationToTeamMateQualifications(Qualification qualification)
{
   teamMateQualifications.append(qualification);
}

void ProjectPartnerProfile::removeQualificationFromPersonalQualifications(Qualification qualification)
{
    int index = personalQualifications.indexOf(qualification);

    if (index != -1)
    {
        personalQualifications.remove(index);
    }
}

void ProjectPartnerProfile::removeQualificationFromTeamMateQualifications(Qualification qualification)
{
    int index = teamMateQualifications.indexOf(qualification);

    if (index != -1)
    {
        teamMateQualifications.remove(index);
    }
}

bool ProjectPartnerProfile::hasPersonalQualification(Qualification qualification)
{
    return personalQualifications.contains(qualification);
}

bool ProjectPartnerProfile::hasTeamMateQualification(Qualification qualification)
{
    return teamMateQualifications.contains(qualification);
}

QVector<Qualification> ProjectPartnerProfile::getPersonalQualifications()
{
    return personalQualifications;
}

QVector<Qualification> ProjectPartnerProfile::getQualifications()
{
    return teamMateQualifications + personalQualifications;
}

void ProjectPartnerProfile::addQualification(int index,Qualification qualification)
{
    qualifications[index] = qualification;
}


