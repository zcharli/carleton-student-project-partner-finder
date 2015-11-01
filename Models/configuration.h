#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define NUMBER_OF_CONFIGURATIONS 1

enum ConfigurationType
{
    TeamSize = 0,
    NoType
};

class Configuration
{
    ConfigurationType type;
    int value;

public:
    Configuration(ConfigurationType=NoType, int=0);

    static Configuration* DefaultConfiguration();

    /*!
     *       @param: none
     *        @desc: get the configuration type
     *      @return: type: ConfigurationType
     */
    ConfigurationType getType();

    /*!
     *       @param: none
     *        @desc: get the configuration value
     *      @return: value: int
     */
    int getValue();

    /*!
     *       @param: newValue: int
     *        @desc: set the configuration value
     *      @return: void
     */
    void setValue(int);
};

#endif // CONFIGURATION_H
