#ifndef QUALIFICATION_H
#define QUALIFICATION_H

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
};


class Qualification
{
    int value;
    QualificationType type;

public:
    Qualification(QualificationType, int);

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

};

#endif // QUALIFICATION_H
