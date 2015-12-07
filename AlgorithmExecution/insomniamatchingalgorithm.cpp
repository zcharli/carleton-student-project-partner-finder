#include "insomniamatchingalgorithm.h"
#include "errorcodes.h"
#include "DataAccessLayer/projectpartnerprofilereal.h"
#include "DataAccessLayer/projectpartnerprofile.h"
#include "DataAccessLayer/studentuser.h"
#include <qglobal.h>
#include <QDebug>
#include <QTime>
#include <QtAlgorithms>
#include <QPair>

bool compare(ProjectPartnerProfile* first, ProjectPartnerProfile* second)
{
    return first->getPersonalTechnicalScore() > second->getPersonalTechnicalScore();
}

InsomniaMatchingAlgorithm::InsomniaMatchingAlgorithm(Project* project):profiles(project->getRegisteredPPPs())
{
    this->project = project;
    setUpAlgorithmForLaunch();
}

InsomniaMatchingAlgorithm::~InsomniaMatchingAlgorithm()
{
    //TODO: Do clean up here!
    cleanUpMap();
}

int InsomniaMatchingAlgorithm::setUpAlgorithmForLaunch()
{
    foreach (ProjectPartnerProfile* profile, profiles)
    {
        int key = profile->getPersonalTechnicalScore()/10 * 10;

        QVector<ProjectPartnerProfile*>* list = NULL;
        if(profileMaps.contains(key))
        {
            list = profileMaps.value(key);
        }
        else
        {
            list = new QVector<ProjectPartnerProfile*>();
            profileMaps.insert(key, list);
        }

        if(list != NULL)
        {
            list->append(profile);
        }
    }

    //Done populating lists, now we need to sort each of them
    foreach (QVector<ProjectPartnerProfile*> *list, profileMaps.values())
    {
        qSort(list->begin(), list->end(), compare);
    }

    return SUCCESS;
}

QVector<ProjectPartnerProfile*>* InsomniaMatchingAlgorithm::getLowestBucket()
{
    while(!profileMaps.empty())
    {
        QVector<ProjectPartnerProfile*>* lowestBucket = profileMaps.first();
        if(lowestBucket->empty())
        {
            profileMaps.remove(profileMaps.firstKey());
            delete lowestBucket;
        }
        else
        {
            return lowestBucket;
        }
    }

    return NULL;
}

QVector<ProjectPartnerProfile*>* InsomniaMatchingAlgorithm::getImmediateHighestBucketForTechnicalScore(int technicalScore)
{
    int key = technicalScore/10 * 10;
    while(key <= profileMaps.lastKey())
    {
        QVector<ProjectPartnerProfile*>* immediateHighestBucket = profileMaps.value(key);
        if(immediateHighestBucket != NULL)
        {
            if(immediateHighestBucket->empty())
            {
                profileMaps.remove(key);
                delete immediateHighestBucket;
            }
            else
            {
                if(immediateHighestBucket->last()->getPersonalTechnicalScore() >= technicalScore)
                    return immediateHighestBucket;
            }
        }
        key += 10;
    }

    return NULL;
}

QVector<ProjectPartnerProfile*>* InsomniaMatchingAlgorithm::getImmediateLowestBucketForTechnicalScore(int technicalScore)
{
    int key = technicalScore/10 * 10;
    while(key >= profileMaps.firstKey())
    {
        QVector<ProjectPartnerProfile*>* immediateLowestBucket = profileMaps.value(key);
        if(immediateLowestBucket != NULL)
        {
            if(immediateLowestBucket->empty())
            {
                profileMaps.remove(key);
                delete immediateLowestBucket;
            }
            else
            {
                if(immediateLowestBucket->first()->getPersonalTechnicalScore() <= technicalScore)
                    return immediateLowestBucket;
            }
        }
        key -= 10;
    }

    return NULL;
}


QVector<ProjectPartnerProfile*>* InsomniaMatchingAlgorithm::getHighestBucket()
{
    while(!profileMaps.empty())
    {
        QVector<ProjectPartnerProfile*>* highestBucket = profileMaps.last();
        if(highestBucket->empty())
        {
            profileMaps.remove(profileMaps.lastKey());
            delete highestBucket;
        }
        else
        {
            return highestBucket;
        }
    }

    return NULL;
}

void InsomniaMatchingAlgorithm::cleanUpMap()
{
    foreach(QVector<ProjectPartnerProfile*>* list, profileMaps)
    {
        if (list->empty())
        {
            profileMaps.remove(profileMaps.key(list));
            delete list;
        }
    }
}

QPair<LogType,QString> InsomniaMatchingAlgorithm::createLogEntry(LogType type,QString message)
{
    QPair<LogType,QString> logEntry;
    logEntry.first = type;
    logEntry.second = message;
    return logEntry;
}

ProjectPartnerProfile* InsomniaMatchingAlgorithm::getBestCompatibleMemberForTeamInBucket(Team& team, QVector<ProjectPartnerProfile*>* bucket)
{
    int closestIndex = -1;
    float flexMetric = -(team.getTeamSatisfaction())/10.0 * 10.0; //  Need this to prevent truncation
    ProjectPartnerProfile* profile = NULL;
    if(bucket == NULL)
        return NULL;

    //  Attempt to get member based on workethic and technical score
    for (int i = bucket->size()-1; i >= 0; i--)
    {
        ProjectPartnerProfile* potentialTeamMate = bucket->value(i);
        if(potentialTeamMate->getPersonalTechnicalScore() < team.getTeamRequiredTeammateTechScore() + flexMetric) // potential teammate doesn't meet tech score requirement
        {
            //  keep track of the index of the profile that is as close to the TS as possible
            closestIndex = i;
            continue;
        }

        if(checkProfileCompatibleWithTeam(&team, potentialTeamMate) < 3) //  potential teammate isnt compatible in terms of WE
            continue;

        profile = potentialTeamMate;
        QString log = "Added Student: " + profile->getStudentUser().getFirstName() + " "
                + profile->getStudentUser().getLastName() +
                " because user met Work Ethic and Technical Score criteria";

        team.addLog(createLogEntry(AddedStudent,log));
        break;
    }

    if(profile != NULL) // Found a work Ethic and Technical score Match
        return profile;

    //  Attempt to get member based on workethic in the same bucket
    //  This will be done starting from the user that meets the teamTechScore of the team as close as possible to the farthest
    //  Note: If we got here, it means no one satisfied both WE and TS, this consequently means that we have the index of the closest TS profile to start from
    for (int i = closestIndex; i < bucket->size(); i++)
    {
        ProjectPartnerProfile* potentialTeamMate = bucket->value(i);

        if(checkProfileCompatibleWithTeam(&team, potentialTeamMate) < 3) //  potential teammate isnt compatible in terms of WE
            continue;

        profile = potentialTeamMate;
        QString log = "Added Student: " + profile->getStudentUser().getFirstName() + " "
                + profile->getStudentUser().getLastName() +
                " because user met Work Ethic criteria only, but fell within the team satisfaction level.";
        team.addLog(createLogEntry(AddedStudent,log));
        break;
    }

    if(profile != NULL) //Found a member in terms of work ethic only
        return profile;

    //  wasn't able to find anyone compatible for the team in the bucket
    return NULL;
}

ProjectPartnerProfile* InsomniaMatchingAlgorithm::getNextCompatibleMemberForTeam(Team& team)
{
    ProjectPartnerProfile* profile = NULL;
    int keyForTeam = team.getTeamRequiredTeammateTechScore()/10 * 10;
    int flexibility = -(team.getTeamSatisfaction())/10 * 10;
    float flexMetric = -(team.getTeamSatisfaction())/10.0 * 10.0; //  Need this to prevent truncation
    QVector<ProjectPartnerProfile*> teamMateBucket;

    if(flexMetric < 0)
    {
        //  Means we over satisfied the team so we can afford to go lower
        if (team.getMembersInTeam().size() > 1)
        {
            team.addLog(createLogEntry(OverSatisfied,"Algorithm: Over satisfied team's last request. Attempting to relax required teammate score to neutralize satisfaction for team"));
        }

        int key = keyForTeam;
        int Lbound = key + flexibility;
        for (int i = key; (i >= Lbound && i >= 0); i -= 10)
        {
            QVector<ProjectPartnerProfile*>* bucket = profileMaps.value(i, NULL);
            if(bucket != NULL)
            {
                teamMateBucket += *bucket;
            }
        }
    }
    else
    {
        //  Means we under satisfied the team so we have to get higher profiles
        if (team.getMembersInTeam().size() > 1)

        {
            team.addLog(createLogEntry(UnderSatisfied,"Algorithm: Under satisfied team's last request. Attempting to tighten required teammate score to neutralize satisfaction for team"));
        }

        int key = keyForTeam;
        int Ubound = key + flexibility;
        for (int i = key; (i <= Ubound && i < 100); i += 10)
        {
            QVector<ProjectPartnerProfile*>* bucket = profileMaps.value(i, NULL);
            if(bucket != NULL)
            {
                teamMateBucket += *bucket;
            }
        }
    }

    if (!teamMateBucket.empty())
    {
        profile = getBestCompatibleMemberForTeamInBucket(team, &teamMateBucket);
        if (profile == NULL)
        {
            QVector<ProjectPartnerProfile*>* bucket = NULL;
            if(flexMetric < 0) //  oversatisfied
            {
                bucket = getImmediateLowestBucketForTechnicalScore(team.getTeamRequiredTeammateTechScore());
                if (bucket != NULL)
                {
                    profile = bucket->first(); // highest member in immediately lowest bucket
                    QString log = "Edge Case(Unable to find a profile satisfying team criteria) Added Student: " + profile->getStudentUser().getFirstName() + " "
                            + profile->getStudentUser().getLastName() +
                            " because user meets the technical score as close as possible";
                    team.addLog(createLogEntry(AddedStudent,log));
                }
            }
            else  //undersatisfied
            {
                bucket = getImmediateHighestBucketForTechnicalScore(team.getTeamRequiredTeammateTechScore());
                if(bucket != NULL)
                {
                    profile = bucket->last(); // lowest member in immediately highest bucket
                    QString log = "Edge Case(Unable to find a profile satisfying team criteria) Added Student: " + profile->getStudentUser().getFirstName() + " "
                            + profile->getStudentUser().getLastName() +
                            " because user meets the technical score as close as possible";
                    team.addLog(createLogEntry(AddedStudent,log));
                }
            }
        }
    }
    else
    {
        //TODO: NO Profiles within flexibility bounds
        qDebug() << "NO Profiles within flexibility bounds\n";

        QVector<ProjectPartnerProfile*>* bucket = NULL;
        if(flexMetric < 0) //  oversatisfied
        {
            bucket = getImmediateLowestBucketForTechnicalScore(team.getTeamRequiredTeammateTechScore());
            if (bucket != NULL)
            {
                profile = bucket->first(); // highest member in immediately lowest bucket
                QString log = "Edge Case(No Profiles within flexibility bounds of team) Added Student: " + profile->getStudentUser().getFirstName() + " "
                        + profile->getStudentUser().getLastName() +
                        " to neutralize team satisfaction because user meets the technical score as close as possible";
                team.addLog(createLogEntry(AddedStudent,log));
            }
        }
        else  //undersatisfied
        {
            bucket = getImmediateHighestBucketForTechnicalScore(team.getTeamRequiredTeammateTechScore());
            if(bucket != NULL)
            {
                profile = bucket->last(); // lowest member in immediately highest bucket
                QString log = "Edge Case(No Profiles within flexibility bounds of team) Added Student: " + profile->getStudentUser().getFirstName() + " "
                        + profile->getStudentUser().getLastName() +
                        " to neutralize team satisfaction because user meets the technical score as close as possible";
                team.addLog(createLogEntry(AddedStudent,log));
            }
        }
    }

    if(profile == NULL)
    {
        //GET the highest member here
        if(flexMetric < 0)
        {
            QVector<ProjectPartnerProfile*>* bucket = getLowestBucket();
            profile = bucket->first();
            QString log = "Edge Case(No User found to satisfy all conditions of team) Added Student: " + profile->getStudentUser().getFirstName() + " "
                    + profile->getStudentUser().getLastName() +
                    " as extreme measure to neutralize team satisfaction";
            team.addLog(createLogEntry(AddedStudent,log));
        }
        else
        {
            QVector<ProjectPartnerProfile*>* bucket = getHighestBucket();
            profile = bucket->last();
            QString log = "Edge Case(No User found to satisfy all conditions of team) Added Student: " + profile->getStudentUser().getFirstName() + " "
                    + profile->getStudentUser().getLastName() +
                    " as extreme measure to neutralize team satisfaction";
            team.addLog(createLogEntry(AddedStudent,log));
        }
    }

    if(profile != NULL)
    {
        int keyForProfile = profile->getPersonalTechnicalScore()/10 * 10;
        QVector<ProjectPartnerProfile*>* list =  profileMaps.value(keyForProfile);
        list->remove(list->indexOf(profile));
        cleanUpMap();
    }

    return profile;
}

int InsomniaMatchingAlgorithm::checkProfilesCompatible(ProjectPartnerProfile* member1, ProjectPartnerProfile* member2)
{
    unsigned char compatibility = member1->getWorkEthicByte() & member2->getWorkEthicByte();
    return __builtin_popcount(compatibility);
}

int InsomniaMatchingAlgorithm::checkProfileCompatibleWithTeam(Team* team, ProjectPartnerProfile* member)
{
    unsigned char compatibility = team->getTeamWorkEthic() & member->getWorkEthicByte();
    return __builtin_popcount(compatibility);
}

QVector<int> InsomniaMatchingAlgorithm::getTeamSizeConfigurations(int numberOfRegisteredProfiles, int teamSize)
{
    QVector<int> configurations;
    int normalSize = teamSize;
    int abnormalTeamSize = numberOfRegisteredProfiles%teamSize;

    if (abnormalTeamSize > 0)
    {
        int numberNormal = numberOfRegisteredProfiles/teamSize;
        for(int i = 0; i < numberNormal; i++)
            configurations.append(normalSize);

        //  Normalize the configurations
        if(configurations.size() > 0)
        {
          int maxNormalTeamIndex = 0;
          while(maxNormalTeamIndex < configurations.size() && qAbs(abnormalTeamSize - configurations[maxNormalTeamIndex]) > 1)
          {
              configurations[maxNormalTeamIndex]--;
              abnormalTeamSize++;
              maxNormalTeamIndex++;
          }
        }
        configurations.append(abnormalTeamSize);
        qSort(configurations);
    }
    else
    {
        int numberNormal = numberOfRegisteredProfiles/teamSize;
        for(int i = 0; i < numberNormal; i++)
            configurations.append(normalSize);
    }

    return configurations;
}

int InsomniaMatchingAlgorithm::launch(QVector<Team*>& teamsForProject)
{
    int teamSize = project->getProjectConfiguration(TeamSize).getValue();
    QVector<int> teamSizeConfigurations = getTeamSizeConfigurations(profiles.size(), teamSize);
    while(!teamSizeConfigurations.empty())
    {
        Team *team = new Team();
        int sizeForTeam = teamSizeConfigurations.first();
        teamSizeConfigurations.removeFirst();

        QVector<ProjectPartnerProfile*> *highestBucket = getHighestBucket();
        if (highestBucket != NULL)
        {
            //  Get highest possible profile to add to make first member of team
            ProjectPartnerProfile *firstMember = highestBucket->first();
            highestBucket->removeFirst();
            cleanUpMap();
            team->addProfileToTeam(firstMember);
            QString log = "Added Student: " + firstMember->getStudentUser().getFirstName() + " "
                    + firstMember->getStudentUser().getLastName() +
                    " as first member of team, because user currently has the highest technical score ranking";
            team->addLog(createLogEntry(AddedStudent,log));

            // Add other members to team based on compatibility
            for (int j = 0; j < sizeForTeam-1; j++)
            {
                ProjectPartnerProfile *nextMember = getNextCompatibleMemberForTeam(*team);
                if (nextMember == NULL)
                {
                    //TODO: Couldn't find anyone compatible for the team here!! need to do something
                    return ALGORITHM_EXECUTE_ERROR;
                }
                team->addProfileToTeam(nextMember);
            }
            teamsForProject.append(team);
        }
        else
        {
            //Ran out of members
            return ALGORITHM_EXECUTE_ERROR;
        }
    }

    return SUCCESS;
}
