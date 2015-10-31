#include "qualification.h"

Qualification::Qualification(QualificationType type, int value)
{
    this->type = type;
    this->value = value;
}

Qualification* Qualification::DefaultQualifications()
{
    Qualification *array = new Qualification[NUMBER_OF_QUALIFICATIONS];

    for (int i = 0; i < NUMBER_OF_QUALIFICATIONS; i++)
    {
        array[(QualificationType)i] = noneType;
    }

    return array;
}

Qualification Qualification::WorkEthicQualificationFromMapping(bool* mapping)
{
    Qualification qualification(userWorkEthic, 0);

    for (int i = 0; i < 8; i++)
    {
        if (mapping[i])
        {
          SetWorkEthicBitForWorkEthicQualification((WorkEthicQualificationMapping)i, qualification);
        }
    }

    return qualification;
}

void Qualification::WorkEthicMappingFromQualification(Qualification qualification, bool **mapping)
{
  *mapping = new bool[8];

  for (int i = 0; i < 8; i++)
  {
      if (GetWorkEthicBitForWorkEthicQualification((WorkEthicQualificationMapping)i, qualification))
      {
        (*mapping)[i] = true;
      }
      else
      {
        (*mapping)[i] = false;
      }
  }

}

bool Qualification::GetWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping workEthicBit, Qualification& qualification)
{
    unsigned char value = qualification.getValue();

    return (value & (1 << workEthicBit)) >> workEthicBit;
}

void Qualification::SetWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping workEthicBit, Qualification& qualification)
{
    unsigned char newValue = ((unsigned char)qualification.getValue()) | (1 << workEthicBit);

    qualification.setValue(newValue);
}

void Qualification::ClearWorkEthicBitForWorkEthicQualification(WorkEthicQualificationMapping workEthicBit, Qualification& qualification)
{
  unsigned char newValue = ((unsigned char)qualification.getValue()) & (~(1 << workEthicBit));

  qualification.setValue(newValue);
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
