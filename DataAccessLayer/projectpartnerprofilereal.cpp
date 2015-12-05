#include "projectpartnerprofilereal.h"
#include "DataAccessLayer/mapconfigs.h"
#include <QJsonArray>
#include <QDebug>

ProjectPartnerProfileReal::ProjectPartnerProfileReal(StudentUser& user, int pscore, int tscore, unsigned char we, Qualification* qualifications):
ProjectPartnerProfile(user, pscore, tscore, we, qualifications)
{
}

ProjectPartnerProfileReal::~ProjectPartnerProfileReal()
{
}

void ProjectPartnerProfileReal::changeQualification(Qualification newQualification)
{
    qualifications[newQualification.getType()] = newQualification;
}

Qualification ProjectPartnerProfileReal::getQualification(int index)
{
    //TODO: Need to do error checking here.
    return qualifications[index];
}

bool ProjectPartnerProfileReal::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    if(!Qualification::GetWorkEthicBitForWorkEthicQualification(bitPosition, qualifications[userWorkEthic]))
    {
        return false;
    }
    return true;
}

void ProjectPartnerProfileReal::updateProfileScores()
{
    float teamScore = 0;
    float personalScore = 0;

    Qualification::TechnicalScoreForProfile(*this, personalScore, teamScore);
    personalTechnicalScore = personalScore;
    teammateTechnicalScore = teamScore;
    workEthic = (unsigned char)(this->qualifications[userWorkEthic].getValue());

    //TODO: technical normalizations for profile
}

QString ProjectPartnerProfileReal::getTechnicalScores()
{
    return "(" + QString::number(personalTechnicalScore) + ", " + QString::number(teammateTechnicalScore) + ")";
}

bool ProjectPartnerProfileReal::serializeJSONForSave(QJsonObject& pppJSON)
{
    int i;
    if(pppID != 0)
    {
        pppJSON[PPP_pppID] = pppID;
    }

    pppJSON[PPP_personalTechnicalScore] = personalTechnicalScore;
    pppJSON[PPP_teammateTechnicalScore] = teammateTechnicalScore;
    pppJSON[PPP_workEthic] = workEthic;

    if(qualifications != NULL)
    {
        QJsonArray qualificationsArray;

        for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
        {
            QJsonObject qualification;
            qualifications[i].serializeJSONForSave(qualification);
            qualificationsArray.append(qualification);
        }

        pppJSON[QUALIFICATIONS_KEY] = qualificationsArray;
    }

    return true;
}

bool ProjectPartnerProfileReal::deserializeJSONFromRetrieve(const QJsonObject& pppJSON)
{
    if(pppJSON.isEmpty())
    {
        return false;
    }

    // There are some cases where perosnal and teammate tech scores are NOT
    // pulled in for the logged in user
    // tech score are pulled in for when the algorithm needs them
    int i;
    pppID = pppJSON[PPP_pppID].toInt();
    if(pppJSON.contains(PPP_personalTechnicalScore))
    {
        personalTechnicalScore = pppJSON[PPP_personalTechnicalScore].toInt();
        teammateTechnicalScore = pppJSON[PPP_teammateTechnicalScore].toInt();
        workEthic = (unsigned char)pppJSON[PPP_workEthic].toInt();
    }

    if(pppJSON.contains(QUALIFICATIONS_KEY))
    {
        QJsonArray qualificationsArray = pppJSON[QUALIFICATIONS_KEY].toArray();
        for(i=0;i<qualificationsArray.size();++i)
        {
            QJsonObject qualification = qualificationsArray[i].toObject();
            qualifications[i].deserializeJSONFromRetrieve(qualification);
        }
    }

    if(pppJSON.contains(USER_KEY))
    {
        QJsonObject userJson = pppJSON[USER_KEY].toObject();
        user.deserializeJSONFromRetrieve(userJson);
    }

    user.setFetchIDForPPP(pppID);


    return true;
}
