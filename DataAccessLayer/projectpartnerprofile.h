#ifndef PROJECTPARTNERPROFILE_H
#define PROJECTPARTNERPROFILE_H

#include "qualification.h"
#include <QString>

/** Abstract class!!!!
  * Using the Proxy design pattern, so subclasses implement the Functions
  * in their own specific way:
  * The proxy class intercepts functions as much as possible until
  * it deems it necessary to load the actual PPPReal
  */

//forward declarations
class StudentUser;

class ProjectPartnerProfile
{
protected:
    StudentUser& user;
    Qualification *qualifications;
    int pppID;
    int personalTechnicalScore;
    int teammateTechnicalScore;
    unsigned char workEthic;

public:
    ProjectPartnerProfile(StudentUser&,int,int,unsigned char, Qualification*);
    virtual ~ProjectPartnerProfile();

    //accessor Functions
    /*!
     *       @param: none
     *        @desc: get the StudentUser who owns the current PPP
     *      @return: owner: StudentUser&
     */
     StudentUser& getStudentUser();

    /****************************************************************************/
    //                    Pure Virtual Functions                                //
    /****************************************************************************/
    /*!
     *       @param: qualificationToChange: Qualification
     *        @desc: changes the value of the given qualification
     *      @return: void
     */
    virtual void changeQualification(Qualification) = 0;

    /*!
     *       @param: qualificationIndex: int
     *        @desc: gets the given qualification for the specified index
     *      @return: Qualification
     */
    virtual Qualification getQualification(int) = 0;
    /****************************************************************************/

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
     *        @desc: gets the work ethic byte
     *      @return: workEthic: char
     */
     unsigned char getWorkEthicByte();


    /*!
     *       @param: workEthic: char
     *        @desc: sets the work ethic char
     *      @return: none
     */
     void setWorkEthicByte(unsigned char);

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

};

#endif // PROJECTPARTNERPROFILE_H
