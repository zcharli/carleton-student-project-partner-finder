#include "configuration.h"

Configuration::Configuration(ConfigurationType type, int value)
{
    this->type = type;
    this->value = value;
}

ConfigurationType Configuration::getType()
{
    return type;
}


int Configuration::getValue()
{
    return value;
}


void setValue(int newValue)
{
    value = newValue;
}


Configuration* Configuration::DefaultConfiguration()
{
    Configuration *configs = new Configration[NUMBER_OF_CONFIGURATIONS];

    for (int i = 0; i < NUMBER_OF_CONFIGURATIONS; i++)
        configs[i] = Configuration();

    return configs;
}
