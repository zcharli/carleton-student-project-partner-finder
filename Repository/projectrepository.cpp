#include "projectrepository.h"
#include "Models/project.h"

ProjectRepository::ProjectRepository()
{}

ProjectRepository::~ProjectRepository()
{}

unsigned int ProjectRepository::save(const Project& projectObj)
{
    return 0;
}

unsigned int ProjectRepository::deleteFromRepo(const int idToDelete)
{
    return 0;
}

Project& ProjectRepository::fetchById(const int idToFetch)
{
    QString i = "";
    QString b = "";
    Project placeholder(i,b);
    return placeholder;
}

QVector<Project*>& ProjectRepository::fetchAll(const int idToFetch)
{
    QVector<Project*> placeholder;
    return placeholder;
}

unsigned int ProjectRepository::registerPPPToProject(const int userId, const int projectID)
{
    return 0;
}

unsigned int ProjectRepository::unRegisterPPPFromProject(const int userId, const int projectID)
{
    return 0;
}
