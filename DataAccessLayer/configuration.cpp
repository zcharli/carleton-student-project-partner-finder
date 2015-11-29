#include "configuration.h"
#include <QJsonObject>
#include "mapconfigs.h"

Configuration::Configuration(ConfigurationType type, int value) :
    type(type), value(value)
{

}

Configuration::Configuration(const QJsonObject& configJSON)
{
    deserializeJSONFromRetrieve(configJSON);
}

ConfigurationType Configuration::getType()
{
    return type;
}


int Configuration::getValue()
{
    return value;
}


void Configuration::setValue(int newValue)
{
    value = newValue;
}

Configuration* Configuration::DefaultConfigurations()
{
    Configuration *configs = new Configuration[NUMBER_OF_CONFIGURATIONS];

    for (int i = 0; i < NUMBER_OF_CONFIGURATIONS; i++)
        configs[i] = Configuration();

    return configs;
}

bool Configuration::serializeJSONForSave(QJsonObject& configJSON)
{
    configJSON[CONFIGURATION_type] = (int)type;
    configJSON[CONFIGURATION_value] = value;
    return true;
}

bool Configuration::deserializeJSONFromRetrieve(const QJsonObject& configJSON)
{
    type = (ConfigurationType) (configJSON.value(CONFIGURATION_type).toInt());
    value = configJSON.value(CONFIGURATION_value).toInt();
    return true;
}
