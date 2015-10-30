#ifndef PROJECTPARTNERPROFILE_H
#define PROJECTPARTNERPROFILE_H

#include <QVector>
#include <QString>

//forward declarations
class StudentUser;
class Qualification;

class ProjectPartnerProfile
{
    StudentUser& user;
    QString biography;
    QVector<Qualification> personalQualifications;
    QVector<Qualification> teamMateQualifications;
    Qualification *qualifications;
    int pppID;

public:
    ProjectPartnerProfile(StudentUser&, QString&);
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
     *       @param: qualificationToAdd: Qualification
     *        @desc: add the specified qualification to the list of the ownwers PPP qualifications
     *      @return: void
     */
    void addQualificationToPersonalQualifications(Qualification qualification);

    /*!
     *       @param: qualificationToAdd: Qualification
     *        @desc: add the specified qualification to the list of the ownwer's potential teammates' PPP qualifications
     *      @return: void
     */
    void addQualificationToTeamMateQualifications(Qualification qualification);

    /*!
     *       @param: qualificationToRemove: Qualification
     *        @desc: remove the specified qualification from the list of the ownwers PPP qualifications
     *               (if the qualification is contained in the list). Does nothing otherwise
     *      @return: void
     */
    void removeQualificationFromPersonalQualifications(Qualification qualification);

    /*!
     *       @param: qualificationToRemove: Qualification
     *        @desc: remove the specified qualification from the list of the ownwer's potential teammates' PPP qualifications
     *               (if the qualification is contained in the list). Does nothing otherwise
     *      @return: void
     */
    void removeQualificationFromTeamMateQualifications(Qualification qualification);

    /*!
     *       @param: qualificationToCheck: Qualification
     *        @desc: check if the PPP has the given personal qualification
     *      @return: hasQualification: bool
     */
    bool hasPersonalQualification(Qualification qualification);

    /*!
     *       @param: qualificationToCheck: Qualification
     *        @desc: check if the PPP has the given teammate qualification
     *      @return: hasQualification: bool
     */
    bool hasTeamMateQualification(Qualification qualification);

    /*!
     *       @param: none
     *        @desc: returns all qualifications
     *      @return: personalQualifications: QVection<Qualification>
     */
    QVector<Qualification> getPersonalQualifications();

    /*!
     *       @param: none
     *        @desc: returns all qualifications
     *      @return: teamMateQualifications: QVection<Qualification>
     */
    QVector<Qualification> getQualifications();

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

    /*!
     *       @param: index, qualificationToAdd: int, Qualification
     *        @desc: add the specified qualification to the list of the owner's qualifications
     *      @return: void
     */
    void addQualification(int index,Qualification qualification);

};

#endif // PROJECTPARTNERPROFILE_H
