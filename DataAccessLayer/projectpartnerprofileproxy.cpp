#include "projectpartnerprofileproxy.h"

ProjectPartnerProfileProxy::ProjectPartnerProfileProxy(StudentUser& user):
ProjectPartnerProfile(user, 0, 0, 0)
{
  if(user.profile)
  {
      delete user.profile;
      user.profile = NULL;
  }
  user.profile = this;
  qualifications = Qualification::DefaultQualifications();
  pppID = 0;
  ppp = NULL;
}


ProjectPartnerProfileReal& ProjectPartnerProfileProxy::loadPPP()
{
    if (ppp == NULL)
    {
        //  Load PPP from database here!
        ppp = new ProjectPartnerProfileReal(user, 0, 0, 0);
    }

    return *ppp;
}

void ProjectPartnerProfileProxy::changeQualification(Qualification qualification)
{
    loadPPP().changeQualification(qualification);
}

Qualification ProjectPartnerProfileProxy::getQualification(int index)
{
    loadPPP().getQualification(index);
}
