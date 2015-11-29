#include "configuration.h"
#include <QJsonObject>

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
    configJSON["type"] = (int)type;
    configJSON["value"] = value;
    return true;
}

bool Configuration::deserializeJSONFromRetrieve(const QJsonObject& configJSON)
{
    type = (ConfigurationType) (configJSON.value("type").toInt());
    value = configJSON.value("value").toInt();
    return true;
}
