#ifndef PROJECTPARTNERPROFILEREAL_H
#define PROJECTPARTNERPROFILEREAL_H

#include "projectpartnerprofile.h"

class ProjectPartnerProfileReal : public ProjectPartnerProfile
{
public:
    ProjectPartnerProfileReal(StudentUser&,int,int,unsigned char, Qualification*);
    virtual ~ProjectPartnerProfileReal();

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

#endif // PROJECTPARTNERPROFILEREAL_H
