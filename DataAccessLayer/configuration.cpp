#include "configuration.h"
#include <QJsonObject>

Configuration::Configuration(ConfigurationType type, int value) :
    type(type), value(value)
{

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

    configJSON["type"] = type;
    configJSON["value"] = value;

    return true;
}

bool Configuration::deserializeJSONFromRetrieve(const QJsonObject& configJSON)
{
    QJsonValue res = configJSON.value("type");
    type = (ConfigurationType) (configJSON.value("type").toInt());
    value = configJSON.value("value").toInt();
    return true;
}
