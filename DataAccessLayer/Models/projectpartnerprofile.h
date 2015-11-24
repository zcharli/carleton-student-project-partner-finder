#ifndef PROJECTPARTNERPROFILE_H
#define PROJECTPARTNERPROFILE_H

#include "qualification.h"

#include <QString>

//forward declarations
class StudentUser;

class ProjectPartnerProfile
{
    StudentUser& user;
    Qualification *qualifications;
    int pppID;
    int personalTechnicalScore;
    int teammateTechnicalScore;
    char workEthic;

public:
    ProjectPartnerProfile(StudentUser&,int,int,char);
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
     *       @param: ppp id: int
     *        @desc: set the project partner id
     *      @return: none
     */
    void setPPPID(int);

    /*!
     *       @param: none
     *        @desc: returns the score that the user registered their PPP with
     *      @return: personalTechnicalScore: int
     */
    int getPersonalTechnicalScore();

    /*!
     *       @param: personalTechnicalScore: int
     *        @desc: sets the computed personal technical score
     *      @return: none
     */
    void setPersonalTechnicalScore(int);


    /*!
     *       @param: none
     *        @desc: gets the precomputed teammate technical score
     *      @return: teammateTechnicalScore: int
     */
    int getTeammateTechnicalScore();


    /*!
     *       @param: teammateTechnicalScore: int
     *        @desc: sets the precomputed teammate technical score
     *      @return: none
     */
    void setTeammateTechnicalScore(int);


    /*!
     *       @param: none
     *        @desc: gets the work ethic byte
     *      @return: workEthic: char
     */
    char getWorkEthicByte();


    /*!
     *       @param: workEthic: char
     *        @desc: sets the work ethic char
     *      @return: none
     */
    void setWorkEthicByte(char);


};

#endif // PROJECTPARTNERPROFILE_H
