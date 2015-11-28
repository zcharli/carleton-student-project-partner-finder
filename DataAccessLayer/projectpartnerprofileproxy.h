#ifndef PROJECTPARTNERPROFILEPROXY_H
#define PROJECTPARTNERPROFILEPROXY_H

#include "projectpartnerprofile.h"
#include "projectpartnerprofilereal.h"

class ProjectPartnerProfileProxy : public ProjectPartnerProfile
{
    ProjectPartnerProfileReal *ppp;

    ProjectPartnerProfileReal& loadPPP();

public:
    ProjectPartnerProfileProxy(StudentUser&);

    /*!
     *       @param: qualificationToChange: Qualification
     *        @desc: changes the value of the given qualification
     *      @return: void
     */
    virtual void changeQualification(Qualification);

    /*!
     *       @param: qualificationIndex: int
     *        @desc: gets the given qualification for the specified index
     *      @return: Qualification
     */
    virtual Qualification getQualification(int);
};

#endif // PROJECTPARTNERPROFILEPROXY_H
