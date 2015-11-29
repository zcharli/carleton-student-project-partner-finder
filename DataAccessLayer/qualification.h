#ifndef QUALIFICATION_H
#define QUALIFICATION_H

#include "studentuser.h"
#include "imappable.h"

class QJsonObject;

#define NUMBER_OF_WORK_ETHICS_QUALIFICATIONS 8
#define NUMBER_OF_QUALIFICATIONS 24

enum QualificationType
{
    userCGPA = 0,
    userOO,
    userUI,
    userScripting,
    userDB,
    userDesignPatterns,
    userDataStructures,
    userComputerSecurity,
    userSoftwareDocumentation,
    userNetworkComputing,
    userVersionControl,
    userWebDevelopment,
    userWorkEthic,
    teamMateOO,
    teamMateUI,
    teamMateScripting,
    teamMateDB,
    teamMateDesignPatterns,
    teamMateDataStructures,
    teamMateComputerSecurity,
    teamMateSoftwareDocumentation,
    teamMateNetworkComputing,
    teamMateVersionControl,
    teamMateWebDevelopment,
    noneType
};

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

class Qualification : private IMappable
{
    int value;
    QualificationType type;

public:
    Qualification(QualificationType=noneType, int=0);
    Qualification(const QJsonObject&);

    /*!     returns a qualifications array defaulted to the correct indexes that match
     *      The QualificationType. the values are initialized to zero
     */
    static Qualification* DefaultQualifications();

    /*!
     *  @param:   arrayOfMappings: WorkEthicQualificationMapping*
     *   @desc:   Creates a workEthic entity bit mapping given an array of WorkEthicQualificationMapping
     *            The values in the given mapping array must be inline with the sequence of the enum
     *            definition of the WorkEthicQualificationMapping.
     *  @retuns:  workEthicQualifiction: Qualification
     */
    static Qualification WorkEthicQualificationFromMapping(int[]);

    /*!
     *  @param:   qualificationToParse: Qualification, workEthics: bool** (output)
     *   @desc:   Creates an array of the work ethics values for the given qualification.
                  NOTE: an empty bool** must be sent to this function because it allocates new memory.
     *  @retuns:  none
     */
    static void WorkEthicMappingFromQualification(Qualification, int**);

    /*!
     *  @param:   workEthicBit: WorkEthicMapping, qualifcationInQuestion: Qualification&
     *   @desc:   retuns a boolean if the bit for the given workEthic has been set
     *  @retuns:  isSet: bool
     */
    static bool GetWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping, Qualification&);

    /*!
     *  @param:   workEthicBit: WorkEthicMapping, qualifcationInQuestion: Qualification&
     *   @desc:   sets the workEthic bit of the given qualification
     *  @retuns:  void
     */
    static void SetWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping, Qualification&);

    /*!
     *  @param:   workEthicBit: WorkEthicMapping, qualifcationInQuestion: Qualification&
     *   @desc:   clears the workEthic bit of the given qualification
     *  @retuns:  void
     */
    static void ClearWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping, Qualification&);

    /*!
     *  @param:   StudentUserToCalculate: StudentUser&, personalScore: int& output param, teammateScore: int& output param
     *   @desc:   clears the workEthic bit of the given qualification
     *  @retuns:  void
     */
    static void TechnicalScoreForProfile(ProjectPartnerProfile&, float&, float&);


    //overloaded == operator
    bool operator==(Qualification const);

    /*!
     *       @param: none
     *        @desc: get the value of the qualification
     *      @return: value: int
     */
    int getValue();

    /*!
     *       @param: newValue: int
     *        @desc: sets the value of the qualifcation
     *      @return: none
     */
    void setValue(int);

    /*!
     *       @param: none
     *        @desc: get the type of the qualification
     *      @return: value: int
     */
    int getType();

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

#endif // QUALIFICATION_H
