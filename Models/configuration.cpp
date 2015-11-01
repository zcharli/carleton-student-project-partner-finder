#include "configuration.h"

Configuration::Configuration(ConfigurationType type, int value) :
    configType(type), value(value), applicable(true)
{
}

Configuration::Configuration() : applicable(false) {}

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
    applicable = true;
}

void Configuration::setType(ConfigurationType type)
{
    applicable = true;
    configType = type;
}

bool Configuration::isUsed()
{
    return applicable;
}
