#ifndef PROJECTPARTNERPROFILEPROXY_H
#define PROJECTPARTNERPROFILEPROXY_H

#include "projectpartnerprofile.h"
#include "projectpartnerprofilereal.h"

class ProjectPartnerProfileProxy : public ProjectPartnerProfile
{
    ProjectPartnerProfileReal *ppp;

    ProjectPartnerProfileReal& loadPPP();

public:
    ProjectPartnerProfileProxy(StudentUser&,int,int,unsigned char);
    virtual ~ProjectPartnerProfileProxy();

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

    /*!
     *       @param: qualificationIndex: int
     *        @desc: gets the given qualification for the specified index
     *      @return: Qualification
     */
     virtual bool hasWorkEthic(WorkEthicQualificationMapping);

    /*!
     *       @param: none
     *        @desc: uses the static Qualification class to update the
     *               technical scores
     *      @return: none
     */
    virtual void updateProfileScores();
};

#endif // PROJECTPARTNERPROFILEPROXY_H
