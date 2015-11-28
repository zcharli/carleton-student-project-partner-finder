#ifndef PROJECTPARTNERPROFILEREAL_H
#define PROJECTPARTNERPROFILEREAL_H

#include "projectpartnerprofile.h"

class ProjectPartnerProfileReal : public ProjectPartnerProfile
{
public:
    ProjectPartnerProfileReal(StudentUser&,int,int,unsigned char, Qualification*);

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

#endif // PROJECTPARTNERPROFILEREAL_H
