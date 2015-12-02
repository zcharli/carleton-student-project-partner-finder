#include "team.h"
#include "errorcodes.h"

Team::Team()
{
    teamWorkEthic = 0;
    teamTechScore = 0;
    teamRequiredTeammateTechScore = 0;
    satisfaction = 0;
}

Team::~Team()
{

}

QVector<ProjectPartnerProfile*>& Team::getMembersInTeam()
{
    return profiles;
}


int Team::addProfileToTeam(ProjectPartnerProfile* profile)
{
    profiles.append(profile);
    changeTeamParametersForNewlyAddedTeammember(*profile);
    return SUCCESS;
}

int Team::getTeamSize()
{
    return profiles.size();
}

QStringList& Team::getMatchSummaryForTeam()
{
  return matchSummaryForTeam;
}

int Team::changeTeamParametersForNewlyAddedTeammember(ProjectPartnerProfile& profile)
{

    if (profiles.size() == 1)
    {
        //Just added this member, so we dont have to normalize here
        teamWorkEthic = profile.getWorkEthicByte();
        teamTechScore = profile.getPersonalTechnicalScore();
        teamRequiredTeammateTechScore = profile.getTeammateTechnicalScore();
        satisfaction = 0;
    }
    else
    {
        //  Need to normalize here
        teamWorkEthic = teamWorkEthic | profile.getWorkEthicByte();
        satisfaction += profile.getPersonalTechnicalScore() - teamRequiredTeammateTechScore;
        teamTechScore = (teamTechScore + profile.getPersonalTechnicalScore())/2;
        teamRequiredTeammateTechScore = (teamRequiredTeammateTechScore + profile.getTeammateTechnicalScore())/2;


    }

    return SUCCESS;
}


char Team::getTeamWorkEthic()
{
    return teamWorkEthic;
}

int Team::getTeamTechScore()
{
    return teamTechScore;
}

int Team::getTeamRequiredTeammateTechScore()
{
    return teamRequiredTeammateTechScore;
}

int Team::getTeamSatisfaction()
{
    return satisfaction;
}
