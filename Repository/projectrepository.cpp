#include "projectrepository.h"
#include "Models/project.h"
#include "Models/user.h"

ProjectRepository::ProjectRepository(QSqlDatabase& db)
{
    this->db = db;
}

ProjectRepository::~ProjectRepository()
{}

int ProjectRepository::userCreatedProject(User &user, Project &project)
{
    //TODO:
    return 0;
}

int ProjectRepository::fetchProjectForUser(User &user, Project &project)
{
    //TODO:
    return 0;
}

int ProjectRepository::userUpdatedProject(User &user, Project &project)
{
    //TODO:
    return 0;
}

int ProjectRepository::fetchAllProjects(User &user, QVector<Project *>& projects)
{
    //TODO:
    return 0;
}

int ProjectRepository::fetchProjectsForUser(User &user, QVector<Project *>& projects)
{
    //TODO:
    return 0;
}

int ProjectRepository::userRegisteredInProject(User &user, Project &project)
{
    //TODO:
    return 0;
}

int ProjectRepository::userUnregisteredFromProject(User &user, Project &project)
{
    //TODO:
    return 0;
}

int ProjectRepository::fetchPPPsForProject(User &user, Project &project)
{
    //TODO:
    return 0;
}
