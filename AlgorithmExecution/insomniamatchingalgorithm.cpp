#include "insomniamatchingalgorithm.h"
#include "DataAccessLayer/projectpartnerprofilereal.h"
#include "DataAccessLayer/projectpartnerprofile.h"
#include "DataAccessLayer/studentuser.h"
#include <qglobal.h>
#include <QDebug>
#include <QTime>
#include <QtAlgorithms>

bool compare(ProjectPartnerProfile* first, ProjectPartnerProfile* second)
{
    return first->getPersonalTechnicalScore() > second->getPersonalTechnicalScore();
}

InsomniaMatchingAlgorithm::InsomniaMatchingAlgorithm(Project* project)
{
    this->project = project;

    //  Testing
    QString fname, lname, uname = "";
    StudentUser testUser = StudentUser(fname, lname, uname);

    for (int i = 0; i < 54; i++)
    {
        int pscore = qrand() % ((100) - 60) + 60;
        int tscore = qrand() % ((100) - 60) + 60;
        unsigned char we = i % 2 == 0 ? 218 : 155;
        ProjectPartnerProfile *profile = new ProjectPartnerProfileReal(testUser, pscore, tscore, we);

        profiles.append(profile);
    }
    /// End of Testing

    setUpAlgorithmForLaunch();
}

int InsomniaMatchingAlgorithm::setUpAlgorithmForLaunch()
{
    //TODO: WIll have to do querying for PPPs registered in project here
    foreach (ProjectPartnerProfile* profile, projects)
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
    launch();
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

ProjectPartnerProfile* InsomniaMatchingAlgorithm::getBestCompatibleMemberForTeamInBucket(Team& team, QVector<ProjectPartnerProfile*>* bucket)
{
  ProjectPartnerProfile* profile = NULL;
  if(bucket == NULL)
      return NULL;

  //  Attempt to get member based on workethic and technical score
  for (int i = bucket->size()-1; i >= 0; i--)
  {
      ProjectPartnerProfile* potentialTeamMate = bucket->value(i);
      if(potentialTeamMate->getPersonalTechnicalScore() < team.getTeamRequiredTeammateTechScore()) // potential teammate doesn't meet tech score requirement
          continue;

      if(checkProfileCompatibleWithTeam(&team, potentialTeamMate) < 3) //  potential teammate isnt compatible in terms of WE
          continue;

      profile = potentialTeamMate;
      break;
  }

  if(profile != NULL) // Found a work Ethic and Technical score Match
      return profile;

  //  Attempt to get member based on workethic in the same bucket
  for (int i = bucket->size()-1; i >= 0; i--)
  {
      //  As an optimization, we only have to check the profiles that were less than the required teammatescore here.
      ProjectPartnerProfile* potentialTeamMate = bucket->value(i);
      if(potentialTeamMate->getPersonalTechnicalScore() >= team.getTeamRequiredTeammateTechScore()) // stop checking from here to optimize
          break;

      if(checkProfileCompatibleWithTeam(&team, potentialTeamMate) < 3) //  potential teammate isnt compatible in terms of WE
          continue;

      profile = potentialTeamMate;
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
    int keyForTeam = team.getTeamTechScore()/10 * 10;
    int flexibility = -(team.getTeamSatisfaction())/10 * 10;
    QVector<ProjectPartnerProfile*> teamMateBucket;

    if(flexibility < 0)
    {
        //  Means we over satisfied the team so we can afford to go lower
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
            //TODO: NO Profiles satisfying team flexibility criteria
            //      Get the best highest member in the whole map
            QVector<ProjectPartnerProfile*>* bucket = getHighestBucket();
            if(bucket != NULL)
            {
                profile = bucket->first();
            }
            else
            {
                //  Should never get to this case, but for sanity reasons
                qDebug() << "ERROR: All buckets are empty!\n";
                return NULL;
            }
        }
    }
    else
    {
        //TODO: NO Profiles within flexibility bounds
        qDebug() << "NO Profiles within flexibility bounds\n";

        QVector<ProjectPartnerProfile*>* bucket = getHighestBucket();
        if(bucket != NULL)
        {
            profile = bucket->first();
        }
        else
        {
            //  Should never get to this case, but for sanity reasons
            qDebug() << "ERROR: All buckets are empty!\n";
            return NULL;
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
        int numberAbnormal = 1;
        for(int i = 0; i < numberNormal; i++)
            configurations.append(normalSize);

        //  Normalize the configurations
        int maxNormalTeamIndex = 0;
        while(qAbs(abnormalTeamSize - configurations[maxNormalTeamIndex]) > 1 && maxNormalTeamIndex < configurations.size())
        {
            configurations[maxNormalTeamIndex]--;
            abnormalTeamSize++;
            maxNormalTeamIndex++;
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

int InsomniaMatchingAlgorithm::launch()
{
    int teamSize = 5;
    //TODO: Do preprocess team configuration here
    QVector<int> teamSizeConfigurations = getTeamSizeConfigurations(projects.size(), teamSize);
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

            // Add other members to team based on compatibility
            for (int j = 0; j < sizeForTeam-1; j++)
            {
                ProjectPartnerProfile *nextMember = getNextCompatibleMemberForTeam(*team);
                if (nextMember == NULL)
                {
                    //TODO: Couldn't find anyone compatible for the team here!! need to do something
                    return -1;
                }
                team->addProfileToTeam(nextMember);
            }
            teamsForProject.append(team);
        }
        else
        {
            //Ran out of members
            break;
        }
    }


    int i = 1;
    foreach(Team *team, teamsForProject)
    {
        qDebug() << "TEAM " << i << "("<< team->getTeamTechScore() << ", " << team->getTeamRequiredTeammateTechScore() << ")";
        qDebug() << "Satisfaction: " << team->getTeamSatisfaction();

        foreach(ProjectPartnerProfile* profile, team->getMembersInTeam())
        {
            qDebug() << "--- Member: (" << profile->getPersonalTechnicalScore() << ", " << profile->getTeammateTechnicalScore() << ")";
        }

        i++;

    }
}
