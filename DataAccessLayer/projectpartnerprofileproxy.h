#ifndef PROJECTPARTNERPROFILEPROXY_H
#define PROJECTPARTNERPROFILEPROXY_H

#include "projectpartnerprofile.h"
#include "projectpartnerprofilereal.h"

class QJsoneObject;

class ProjectPartnerProfileProxy : public ProjectPartnerProfile
{
    ProjectPartnerProfileReal *ppp;

    ProjectPartnerProfileReal& loadPPP();

public:
    ProjectPartnerProfileProxy(StudentUser&,int,int,unsigned char);
    virtual ~ProjectPartnerProfileProxy();

    /*!
     *       @param: none
     *        @desc: get the StudentUser who owns the current PPP
     *      @return: owner: StudentUser&
     */
     virtual StudentUser& getStudentUser();

    /*!
     *       @param: none
     *        @desc: get the project partner id
     *      @return: pppID: int
     */
    virtual int getPPPID() const;

    /*!
     *       @param: none
     *        @desc: get the project partner id
     *      @return: pppID: int
     */
    virtual int getPPPID();

    /*!
     *       @param: ppp id: int
     *        @desc: set the project partner id
     *      @return: none
     */
     virtual void setPPPID(int);

    /*!
     *       @param: none
     *        @desc: gets the work ethic byte
     *      @return: workEthic: char
     */
     virtual unsigned char getWorkEthicByte();


    /*!
     *       @param: workEthic: char
     *        @desc: sets the work ethic char
     *      @return: none
     */
     virtual void setWorkEthicByte(unsigned char);

    /*!
     *       @param: none
     *        @desc: returns the score that the user registered their PPP with
     *      @return: personalTechnicalScore: int
     */
     virtual int getPersonalTechnicalScore();

    /*!
     *       @param: personalTechnicalScore: int
     *        @desc: sets the computed personal technical score
     *      @return: none
     */
     virtual void setPersonalTechnicalScore(int);


    /*!
     *       @param: none
     *        @desc: gets the precomputed teammate technical score
     *      @return: teammateTechnicalScore: int
     */
     virtual int getTeammateTechnicalScore();


    /*!
     *       @param: teammateTechnicalScore: int
     *        @desc: sets the precomputed teammate technical score
     *      @return: none
     */
     virtual void setTeammateTechnicalScore(int);

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

    /*!
     *       @param: empty Json Object: QJsonObject&
     *        @desc: serializes the object implementing into JSON
     *      @return: success or failure: bool
     */
    virtual bool serializeJSONForSave(QJsonObject&);

    /*!
     *       @param: objectToDeSerialize: QJsonObject&
     *        @desc: deserializes the the JSON object to create the object back
     *      @return: success or failure: bool
     */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&);
};

#endif // PROJECTPARTNERPROFILEPROXY_H
