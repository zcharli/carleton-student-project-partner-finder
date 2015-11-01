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
};

#endif // CONFIGURATION_H
