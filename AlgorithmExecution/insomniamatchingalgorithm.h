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

    int checkProfilesCompatible(ProjectPartnerProfile*, ProjectPartnerProfile*);
    int checkProfileCompatibleWithTeam(Team*, ProjectPartnerProfile*);
    ProjectPartnerProfile* getNextCompatibleMemberForTeam(Team&);
    ProjectPartnerProfile* getBestCompatibleMemberForTeamInBucket(Team&, QVector<ProjectPartnerProfile*>*);
    QVector<int> getTeamSizeConfigurations(int numberOfRegisteredProfiles, int teamSize);
    int setUpAlgorithmForLaunch();
    QVector<ProjectPartnerProfile*>* getHighestBucket();
    void cleanUpMap();


public:
    InsomniaMatchingAlgorithm();//(Project*);

    int launch();
};

#endif // INSOMNIAMATCHINGALGORITHM_H
