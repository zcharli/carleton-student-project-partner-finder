#include "projectpartnerprofileproxy.h"
#include "dataaccessfacade.h"
#include <QJsonObject>
#include "errorcodes.h"
#include <QJsonObject>
#include "DataAccessLayer/mapconfigs.h"

ProjectPartnerProfileProxy::ProjectPartnerProfileProxy(StudentUser& user, int pScore, int tScore, unsigned char we):
    ProjectPartnerProfile(user, pScore, tScore, we, NULL)
{
    pppID = 0;
    ppp = NULL;
}

ProjectPartnerProfileProxy::~ProjectPartnerProfileProxy()
{
    if(ppp != NULL)
        delete ppp;
}

ProjectPartnerProfileReal& ProjectPartnerProfileProxy::loadPPP()
{
    if (ppp == NULL)
    {
        //  Load PPP from database here!
        int SUCCESS_STATUS = SUCCESS;
        QJsonObject realPPPJson;
        ppp = new ProjectPartnerProfileReal(user, 0, 0, 0, Qualification::DefaultQualifications());
        ppp->setPPPID(this->user.getFetchIDForPPP());
        ppp->serializeJSONForSave(realPPPJson);
        SUCCESS_STATUS = DataAccessFacade::managedDataAccess().getDispatcher().retrievePPPForUser(realPPPJson, true);
        if(SUCCESS_STATUS == SUCCESS)
        {
            ppp->deserializeJSONFromRetrieve(realPPPJson);
        }

    }

    return *ppp;
}

void ProjectPartnerProfileProxy::changeQualification(Qualification qualification)
{
    loadPPP().changeQualification(qualification);
}

Qualification ProjectPartnerProfileProxy::getQualification(int index)
{
    return loadPPP().getQualification(index);
}

bool ProjectPartnerProfileProxy::hasWorkEthic(WorkEthicQualificationMapping bitPosition)
{
    return loadPPP().hasWorkEthic(bitPosition);
}

void ProjectPartnerProfileProxy::updateProfileScores()
{
    loadPPP().updateProfileScores();

    this->workEthic = loadPPP().getWorkEthicByte();
    this->personalTechnicalScore = loadPPP().getPersonalTechnicalScore();
    this->teammateTechnicalScore = loadPPP().getTeammateTechnicalScore();
}

StudentUser& ProjectPartnerProfileProxy::getStudentUser()
{
    if(ppp != NULL)
        return loadPPP().getStudentUser();

    return user;
}

int ProjectPartnerProfileProxy::getPPPID() const
{
    if(ppp != NULL)
    {
        const ProjectPartnerProfileReal& real = *ppp;
        return real.getPPPID();
    }

    return pppID;
}

int ProjectPartnerProfileProxy::getPPPID()
{
    if(ppp != NULL)
        return loadPPP().getPPPID();

    return pppID;
}

void ProjectPartnerProfileProxy::setPPPID(int id)
{
    if(ppp != NULL)
        loadPPP().setPPPID(id);

    pppID = id;
}

unsigned char ProjectPartnerProfileProxy::getWorkEthicByte()
{
    if(ppp != NULL)
        return loadPPP().getWorkEthicByte();

    return workEthic;
}

void ProjectPartnerProfileProxy::setWorkEthicByte(unsigned char we)
{
    if(ppp != NULL)
        loadPPP().setWorkEthicByte(we);

    workEthic = we;
}

int ProjectPartnerProfileProxy::getPersonalTechnicalScore()
{
    if(ppp != NULL)
        return loadPPP().getPersonalTechnicalScore();

    return personalTechnicalScore;
}

void ProjectPartnerProfileProxy::setPersonalTechnicalScore(int ps)
{
    if(ppp != NULL)
        loadPPP().setPersonalTechnicalScore(ps);

    personalTechnicalScore = ps;
}

int ProjectPartnerProfileProxy::getTeammateTechnicalScore()
{
    if(ppp != NULL)
        return loadPPP().getTeammateTechnicalScore();

    return teammateTechnicalScore;
}

QString ProjectPartnerProfileProxy::getTechnicalScores()
{
    if(ppp != NULL)
        return loadPPP().getTechnicalScores();

    return "(" + QString::number(personalTechnicalScore) + ", " + QString::number(teammateTechnicalScore) + ")";
}

void ProjectPartnerProfileProxy::setTeammateTechnicalScore(int ts)
{
    if(ppp != NULL)
        loadPPP().setTeammateTechnicalScore(ts);

    teammateTechnicalScore = ts;
}

bool ProjectPartnerProfileProxy::serializeJSONForSave(QJsonObject& pppJSON)
{
    if(ppp != NULL)
        return loadPPP().serializeJSONForSave(pppJSON);

    if(pppID != 0)
    {
        pppJSON[PPP_pppID] = pppID;
    }

    pppJSON[PPP_personalTechnicalScore] = personalTechnicalScore;
    pppJSON[PPP_teammateTechnicalScore] = teammateTechnicalScore;
    pppJSON[PPP_workEthic] = workEthic;
    return true;
}


bool ProjectPartnerProfileProxy::deserializeJSONFromRetrieve(const QJsonObject& pppJSON)
{
    if(ppp != NULL)
    {
        pppID = pppJSON[PPP_pppID].toInt();
        return loadPPP().deserializeJSONFromRetrieve(pppJSON);
    }

    if(pppJSON.isEmpty())
    {
        return false;
    }

    // There are some cases where perosnal and teammate tech scores are NOT
    // pulled in for the logged in user
    // tech score are pulled in for when the algorithm needs them
    pppID = pppJSON[PPP_pppID].toInt();
    if(pppJSON.contains(PPP_personalTechnicalScore))
    {
        personalTechnicalScore = pppJSON[PPP_personalTechnicalScore].toInt();
        teammateTechnicalScore = pppJSON[PPP_teammateTechnicalScore].toInt();
        workEthic = (unsigned char)pppJSON[PPP_workEthic].toInt();
    }

    if(pppJSON.contains(USER_KEY))
    {
        QJsonObject userJson = pppJSON[USER_KEY].toObject();
        user.deserializeJSONFromRetrieve(userJson);
    }

    return true;
}
