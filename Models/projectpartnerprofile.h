#ifndef PROJECTPARTNERPROFILE_H
#define PROJECTPARTNERPROFILE_H

#include <QString>
#include "Models/qualification.h"

//forward declarations
class StudentUser;

class ProjectPartnerProfile
{
    StudentUser& user;
    Qualification *qualifications;
    int pppID;

public:
    ProjectPartnerProfile(StudentUser&);
    ~ProjectPartnerProfile();

    //accessor Functions
    /*!
     *       @param: none
     *        @desc: get the StudentUser who owns the current PPP
     *      @return: owner: StudentUser&
     */
    StudentUser& getStudentUser();

    /*!
     *       @param: qualificationToChange: Qualification
     *        @desc: changes the value of the given qualification
     *      @return: void
     */
    void changeQualification(Qualification);

    /*!
     *       @param: qualificationIndex: int
     *        @desc: gets the given qualification for the specified index
     *      @return: Qualification
     */
    Qualification getQualification(int);


    /*!
     *       @param: qualificationIndex: int
     *        @desc: gets the given qualification for the specified index
     *      @return: Qualification
     */
    bool hasWorkEthic(WorkEthicQualificationMapping);

    /*!
     *       @param: none
     *        @desc: get the project partner id
     *      @return: pppID: int
     */
    int getPPPID();

    /*!
     *       @param: id: int
     *        @desc: sets the project partner id
     *      @return: none
     */
    void setPPPID(int id);

};

#endif // PROJECTPARTNERPROFILE_H
