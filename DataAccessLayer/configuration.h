#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define NUMBER_OF_CONFIGURATIONS 1

#include "imappable.h"

class QJsonObject;

enum ConfigurationType
{
    TeamSize = 0,
    NoType
};

class Configuration : private IMappable
{
    ConfigurationType type;
    int value;

public:
    Configuration(ConfigurationType=NoType, int=0);
    Configuration(const QJsonObject&);

    static Configuration* DefaultConfigurations();

    /*!
     *       @param: none
     *        @desc: get the configurations type set by the AdministratorUser on the project
     *      @return: configurationType: ConfigurationType*
     */
    ConfigurationType getType();

    /*!
     *       @param: none
     *        @desc: get the configuration value
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

#endif // CONFIGURATION_H
