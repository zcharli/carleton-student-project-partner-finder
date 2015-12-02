#ifndef TEAM_H
#define TEAM_H

#include <QVector>
#include <QStringList>
#include "DataAccessLayer/qualification.h"
#include "DataAccessLayer/projectpartnerprofile.h"

class Team
{
    QVector<ProjectPartnerProfile*> profiles;
    int teamTechScore;
    int teamRequiredTeammateTechScore;
    int satisfaction;
    QStringList matchSummaryForTeam;
    unsigned char teamWorkEthic;

    /*!
     *       @param: profileToBeAdded: ProjectPartnerProfile&
     *        @desc: takes care of normalising the new technical scores
     *               and work ethic of the team
     *               MUST CALL THIS FUNCTION AFTER THE MEMBER IS ADDED TO THE TEAM
     *      @return: status of the operation: int
     */
    int changeTeamParametersForNewlyAddedTeammember(ProjectPartnerProfile&);

public:
    Team();
    ~Team();

    /*!
     *       @param: none
     *        @desc: returns the members in the team
     *      @return: list Of Team Members: QVector<ProjectPartnerProfile&>&
     */
    QVector<ProjectPartnerProfile*>& getMembersInTeam();

    /*!
     *       @param: profileToAdd: ProjectPartnerProfile&
     *        @desc: add the given profile to the Team
     *      @return: status of the operation: int
     */
    int addProfileToTeam(ProjectPartnerProfile*);

    /*!
     *       @param: none
     *        @desc: get the number of students In the team
     *      @return: number of profiles: int
     */
    int getTeamSize();

    /*!
     *       @param: none
     *        @desc: get team work ethic
     *      @return: teamWorkEthic: char
     */
    char getTeamWorkEthic();

    /*!
     *       @param: none
     *        @desc: get the team techScore
     *      @return: teamTechScore: int
     */
    int getTeamTechScore();

    /*!
     *       @param: none
     *        @desc: get the required team tech score
     *      @return: requiredTeamTechScore: int
     */
    int getTeamRequiredTeammateTechScore();

    /*!
     *       @param: none
     *        @desc: get the current satisfaction of the team
     *      @return: teamSatisfaction: int
     */
    int getTeamSatisfaction();

    /*!
     *       @param: none
     *        @desc: returns the summary of how the team was created
     *      @return: matchSummary: QStringList&
     */
    QStringList& getMatchSummaryForTeam();



};

#endif // TEAM_H
