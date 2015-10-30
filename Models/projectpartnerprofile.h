#ifndef PROJECTPARTNERPROFILE_H
#define PROJECTPARTNERPROFILE_H

#include <QString>

//forward declarations
class StudentUser;
class Qualification;

enum WorkEthicQualificationMapping
{
    dependableBit = 0,
    organizedBit,
    proactiveBit,
    efficientBit,
    humorBit,
    impulsiveBit,
    flexibleBit,
    hardworkingBit
};

#define NUMBER_OF_QUALIFICATIONS 25

class ProjectPartnerProfile
{
    StudentUser& user;
    QString biography;
    Qualification *qualifications;

public:
    ProjectPartnerProfile(StudentUser&, QString&, Qualification*);
    ~ProjectPartnerProfile();

    //accessor Functions
    /*!
     *       @param: none
     *        @desc: get the biography of the PPP
     *      @return: biography: QString&
     */
    QString& getBiography();

    /*!
     *       @param: newBiography: QString&
     *        @desc: set the biography of the PPP
     *      @return: void
     */
     void setBiography(QString& newBiography);

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


};

#endif // PROJECTPARTNERPROFILE_H
