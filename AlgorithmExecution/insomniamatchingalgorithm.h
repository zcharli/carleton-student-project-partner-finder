#ifndef INSOMNIAMATCHINGALGORITHM_H
#define INSOMNIAMATCHINGALGORITHM_H

#include <QVector>
#include <QMap>
#include "team.h"
#include "DataAccessLayer/project.h"

class InsomniaMatchingAlgorithm
{
    Project* project;

    QMap<int, QVector<ProjectPartnerProfile*>* > profileMaps;
    QVector<Team*> teamsForProject;
    QVector<ProjectPartnerProfile*> profiles;

    /*!
     *       @param: ppp1: ProjectPartnerProfile*, ppp2: ProjectPartnerProfile*
     *        @desc: checks to see if ppp1 & ppp2 are compatible based on work ethic
     *               two profiles are compatible if they share 3 out of 5 work ethic traits
     *      @return: numberOfCompatibleTraits: int
     */
    int checkProfilesCompatible(ProjectPartnerProfile*, ProjectPartnerProfile*);


    /*!
     *       @param: ppp1: ProjectPartnerProfile*, ppp2: ProjectPartnerProfile*
     *        @desc: checks to see if ppp1 & ppp2 are compatible based on work ethic
     *               two profiles are compatible if they share 3 out of 5 work ethic traits
     *      @return: numberOfCompatibleTraits: int
     */
    int checkProfileCompatibleWithTeam(Team*, ProjectPartnerProfile*);

    /*!
     *       @param: teamToCreate: Team&
     *        @desc: Finds the next best compatible member for the given team.
     *               This is done in two steps:
     *                - First:  check based on work ethic and qualificaitons
     *                - Second: check based on work ethic only
     *      @return: nextCompatibleProfile: ProjectPartnerPrfile* (NULL if none found)
     */
    ProjectPartnerProfile* getNextCompatibleMemberForTeam(Team&);

    /*!
     *       @param: teamToCreate: Team&, pppBucket: QVector<ProjectPartnerProfile*>
     *        @desc: Helper function for getNextCompatibleMemberForTeam
     *      @return: nextCompatibleProfile: ProjectPartnerPrfile* (NULL if none found)
     */
    ProjectPartnerProfile* getBestCompatibleMemberForTeamInBucket(Team&, QVector<ProjectPartnerProfile*>*);

    /*!
     *       @param: numProfilesRegisteredInProject: int, projectTeamSizeConfiguration: int
     *        @desc: returns a configuration list of team sizes that will cause the difference between the
     *               smallest and largest team to be +1 or 0
     *      @return: teamSizeConfigurations: QVector<int>
     */
    QVector<int> getTeamSizeConfigurations(int numberOfRegisteredProfiles, int teamSize);

    /*!
     *       @param: none
     *        @desc: Gets the algorithm ready for exection.
     *               - All profile fetching from project and algorithm configuration must be done here.
     *      @return: success status: int
     */
    int setUpAlgorithmForLaunch();

    /*!
     *       @param: none
     *        @desc: Finds the currently highest bucket of Profiles
     *      @return: highestProfileBucket: QVector<ProjectPartnerProfile*>* (returns NULL if none found)
     */
    QVector<ProjectPartnerProfile*>* getHighestBucket();

    /*!
     *       @param: none
     *        @desc: Cleans up the map to remove any empty buckets
     *      @return: void
     */
    void cleanUpMap();


public:
    InsomniaMatchingAlgorithm();//(Project*);

    /*!
     *       @param: none
     *        @desc: launches the insomnia algorithm for creating teams on the given profile
     *      @return: algorithmExecution success status: int
     */
    int launch();
};

#endif // INSOMNIAMATCHINGALGORITHM_H
