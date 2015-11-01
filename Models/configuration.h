#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define NUMBER_OF_CONFIGURATIONS 1

// Must start at 1
enum ConfigurationType {
    teamSize = 1
};

class Configuration
{
    ConfigurationType configType;
    int value;
    bool applicable;

public:
    Configuration();
    Configuration(ConfigurationType,int);
    ~Configuration();

    /*!
     *       @param: none
     *        @desc: get the configurations type set by the AdministratorUser on the project
     *      @return: configurationType: ConfigurationType*
     */
    ConfigurationType getType();

    /*!
     *       @param: none
     *        @desc: get the configurations value set by the AdministratorUser on the project
     *      @return: value: int
     */
    int getValue();

    /*!
     *       @param: value: int
     *        @desc: set the configurations value by the AdministratorUser on the project
     *      @return: none
     */
    void setValue(int);

    /*!
     *       @param: type: ConfigurationType
     *        @desc: set the configurations type by the AdministratorUser on the project
     *      @return: none
     */
    void setType(ConfigurationType);

    /*!
     *       @param: none
     *        @desc: a flag to show that this config is applicable to the algorithm (not null)
     *      @return: bool
     */
    bool isUsed();
};

#endif // CONFIGURATION_H
