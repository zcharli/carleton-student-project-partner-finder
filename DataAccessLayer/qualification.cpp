#include "qualification.h"
#include "projectpartnerprofile.h"

#include <QDebug>
#include <QJsonObject>

#define DEFAULT_CGPA 12.0

Qualification::Qualification(QualificationType type, int value)
{
    this->type = type;
    this->value = value;
}

Qualification::Qualification(const QJsonObject& qualificationJSON)
{
    deserializeJSONFromRetrieve(qualificationJSON);
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

void Qualification::TechnicalScoreForProfile(ProjectPartnerProfile& ppp, float codingScore, float& personal, float& teammate)
{
    //TODO: NORMALIZE THE STUDENTUSERS SCORE WITH CGPA AND CODING QUESTION
    int normalizer = (ppp.getQualification(userCGPA) + (codingScore * 100))/(100 + (DEFAULT_CGPA * 10));  //this truncates, but that's what we want

    for (int i = 0; i < NUMBER_OF_QUALIFICATIONS; i++)
    {
        if (i >= 1 && i <= 11)
        {
            personal += ppp.getQualification(i).getValue() * normalizer;
        }
        else if(i >= 13 && i <= 23)
        {
            teammate += ppp.getQualification(i).getValue() * normalizer;
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

bool Qualification::serializeJSONForSave(QJsonObject& qualificationJSON)
{

    qualificationJSON["type"] = (int)type;
    qualificationJSON["value"] = value;

    return true;
}

bool Qualification::deserializeJSONFromRetrieve(const QJsonObject& qualificationJSON)
{
    type = (QualificationType) (qualificationJSON.value("type").toInt());
    value = qualificationJSON.value("value").toInt();
    return true;
}

