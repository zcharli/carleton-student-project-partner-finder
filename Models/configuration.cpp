#include "configuration.h"

Configuration::Configuration(ConfigurationType type, int value) :
    configType(type), value(value)
{
}

Configuration::Configuration() {}

Configuration::~Configuration() {}

ConfigurationType Configuration::getType()
{
    return configType;
}

int Configuration::getValue()
{
    return value;
}

void Configuration::setValue(int val)
{

}

void Configuration::setType(ConfigurationType type)
{
    configType = type;
}
