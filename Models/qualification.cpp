#include "qualification.h"
#include "projectpartnerprofile.h"
#include <QDebug>

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

void Qualification::TechnicalScoreForStudentUser(StudentUser& user, float& personal, float& teammate)
{
    //TODO: NORMALIZE THE STUDENTUSERS SCORE WITH CGPA AND CODING QUESTION

    for (int i = 0; i < NUMBER_OF_QUALIFICATIONS; i++)
    {
        if (i >= 1 && i <= 11)
        {
            personal += user.getProfile()->getQualification(i).getValue();
        }
        else if(i >= 13 && i <= 23)
        {
            teammate += user.getProfile()->getQualification(i).getValue();
        }
    }
}

Qualification Qualification::WorkEthicQualificationFromMapping(int mapping[])
{
    Qualification qualification(userWorkEthic, 0);

    for (int i = 0; i < NUMBER_OF_WORK_ETHICS_QUALIFICATIONS; i++)
    {
        if (mapping[i])
        {
          SetWorkEthicBitForWorkEthicQualification((WorkEthicQualificationMapping)i, qualification);
        }
    }

    return qualification;
}

void Qualification::WorkEthicMappingFromQualification(Qualification qualification, int **mapping)
{
  *mapping = new int[NUMBER_OF_WORK_ETHICS_QUALIFICATIONS];

  for (int i = 0; i < NUMBER_OF_WORK_ETHICS_QUALIFICATIONS; i++)
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
    qDebug() << QString("before: " + QString::number(qualification.getValue()));
    unsigned char newValue = ((unsigned char)qualification.getValue()) | (1 << workEthicBit);
    qDebug() << QString("after: " + QString::number(newValue));
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
