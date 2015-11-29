#include "projectpartnerprofileproxy.h"
#include <QJsonObject>

ProjectPartnerProfileProxy::ProjectPartnerProfileProxy(StudentUser& user, int pScore, int tScore, unsigned char we):
ProjectPartnerProfile(user, pScore, tScore, we, NULL)
{
    user.profile = this;
    pppID = 0;
    ppp = NULL;
}

ProjectPartnerProfileReal& ProjectPartnerProfileProxy::loadPPP()
{
    if (ppp == NULL)
    {
        //  Load PPP from database here!
        ppp = new ProjectPartnerProfileReal(user, 0, 0, 0, NULL);
    }

    return *ppp;
}

void ProjectPartnerProfileProxy::changeQualification(Qualification qualification)
{
    loadPPP().changeQualification(qualification);
}

Qualification ProjectPartnerProfileProxy::getQualification(int index)
{
    return loadPPP().getQualification(index);
}
