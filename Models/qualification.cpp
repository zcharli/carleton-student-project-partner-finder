#include "qualification.h"

Qualification::Qualification(QualificationType type, int value)
{
    this->type = type;
    this->value = value;
}


bool Qualification::operator ==(Qualification const qualification)
{
    return value == qualification.value;
}

int Qualification::getValue()
{
    return value;
}

void Qualification::setValue(int newValue)
{
    value = newValue;
}

int Qualification::getType()
{
    return type;
}
