#include "projectrepository.h"
#include "userrepository.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include <QVector>
#include "QDebug"
#include <QSqlError>
#define NUMBER_OF_CONFIGURATIONS 1

ProjectRepository::ProjectRepository(QSqlDatabase& db)
{
    this->db = db;
}

ProjectRepository::~ProjectRepository()
{}

int ProjectRepository::userCreatedProject(QJsonObject& projectToInsert, int userId)
{
    // Structure is projects -> List of projects
    QJsonObject projectToSave = projectToInsert["projects"].toArray()[0].toObject();
    QJsonObject projectConfigs = projectToSave["configurations"].toObject();
    // An Admin is "registered" to a project by the DB
    QString createProjectQuery = "Insert into project (project_title, project_description) values (:title,:desc)";
    QSqlQuery createProject(this->db);
    createProject.prepare(createProjectQuery);
    createProject.bindValue(":title", projectToSave["title"].toString());
    createProject.bindValue(":desc",projectToSave["description"].toString());

    if(!createProject.exec())
    {
        qDebug() << "userCreatedProject error:  "<< createProject.lastError();
        return createProject.lastError().number();
    }

    int projectID = 0;
    QSqlQuery getProjectID(this->db);
    getProjectID.prepare("Select max(project_id) from project");
    if(getProjectID.exec())
    {
        if(getProjectID.next())
        {
            projectID = getProjectID.value(0).toInt();

        }
    }
    else
    {
        qDebug() << "getProjectID error:  "<< getProjectID.lastError();
        return getProjectID.lastError().number();
    }

    projectToSave["id"] = projectID;
    qDebug() << "Project ID" + QString::number(projectID);

    // Insert configurations
    int i;
    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        QString key = QString::number(i);
        if(projectConfigs.contains(key))
        {
            // Maybe not all configurations are set
            QString insertQualificationQuery = "Insert into project_configurations (config_id,project_id,value) values (:cid, :pid, :val)";
            QSqlQuery insertQualification(this->db);
            insertQualification.prepare(insertQualificationQuery);
            insertQualification.bindValue(":cid",i + 1);
            insertQualification.bindValue(":pid", projectID);
            insertQualification.bindValue(":val",projectConfigs[key].toString());
            if(!insertQualification.exec())
            {
                qDebug() << "insertQualification error:  "<< this->db.lastError();
                return this->db.lastError().number();
            }
        }
    }

    // Register the admin user for this project since ONLY ADMIN can create projects
    QString associateAdmin = "Insert into project_registration (project_id, user_id) values (:pid,:uid)";
    QSqlQuery bindProjectToAdmin(this->db);
    bindProjectToAdmin.prepare(associateAdmin);
    bindProjectToAdmin.bindValue(":pid",projectID);
    bindProjectToAdmin.bindValue(":uid",userId);
    if(!bindProjectToAdmin.exec())
    {
        qDebug() << "bindProjectToAdmin error:  "<< bindProjectToAdmin.lastError();
        return bindProjectToAdmin.lastError().number();
    }

    // Need to replace the copied project object
    projectToInsert["projects"].toArray()[0] = projectToSave;

    return 0;
}

int ProjectRepository::userUpdatedProject(QJsonObject& projectToUpdate, int userId)
{
    QJsonObject projectToSave = projectToUpdate["projects"].toArray()[0].toObject();
    QJsonObject projectConfigs = projectToSave["configurations"].toObject();

    if(!projectToSave.contains("id"))
    {
        return userCreatedProject(projectToUpdate, userId);
    }

    // Update the contents of a project
    QString updateProjQuery = "Update project set project_title=:title , project_description=:desc where project_id=:pid";
    QSqlQuery updateProject(this->db);
    updateProject.prepare(updateProjQuery);
    updateProject.bindValue(":title",projectToSave["title"].toString());
    updateProject.bindValue(":desc",projectToSave["description"].toString());
    updateProject.bindValue(":id",projectToSave["id"].toString());
    if(!updateProject.exec())
    {
        qDebug() << "updateProject error:  "<< updateProject.lastError();
        return updateProject.lastError().number();
    }

    // Update all configurations
    int i;
    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        QString key = QString::number(i);
        if(projectConfigs.contains(key))
        {
            QString updateProjConfigQuery = "Update project_configurations set value=:val where config_id=:cid and project_id=:pid";
            QSqlQuery updateProjConfig(this->db);
            updateProjConfig.prepare(updateProjConfigQuery);
            updateProjConfig.bindValue(":val", projectConfigs[key].toString());
            updateProjConfig.bindValue(":cid",i + 1);
            updateProjConfig.bindValue(":pid",projectToSave["id"].toString());

            if(!updateProjConfig.exec())
            {
                qDebug() << "updateProjConfig error:  "<< this->db.lastError();
                return this->db.lastError().number();
            }
        }
    }

    // Need to replace the copied project object
    projectToUpdate["projects"].toArray()[0] = projectToSave;
    return 0;
}

int ProjectRepository::fetchAllProjects(QJsonObject& allProjectsReturns)
{
    QJsonArray projectsReturned;

    // High running time function.
    // Prepare your garbage cans, here comes the dump
    QString projectDumpQuery = "Select project_id, project_title, project_description from project";
    QSqlQuery fetchAllProjects(this->db);
    fetchAllProjects.prepare(projectDumpQuery);

    int tracker = 0;
    if(fetchAllProjects.exec())
    {
        while(fetchAllProjects.next())
        {
            QJsonObject project;
            QJsonArray projectConfigs;

            // Index
            //  0 -> project_id
            //  1 -> project_title
            //  2 -> project_description

            QString projectTitle = QString(fetchAllProjects.value(1).toString());
            QString projectDescription = QString(fetchAllProjects.value(2).toString());
            int projectId = fetchAllProjects.value(0).toInt();

            // Add project to JSON
            project["id"] = projectId;
            project["title"] = projectTitle;
            project["description"] = projectDescription;

            // Fetch the number of registered users in this project
            QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
            QSqlQuery fetchNumRegistered(this->db);
            fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
            fetchNumRegistered.bindValue(":pid",projectId);
            if(fetchNumRegistered.exec())
            {
                if(fetchNumRegistered.next())
                {
                    // Negate the AdministratorUser from the count
                    project["numberOfRegisteredUsers"] = fetchNumRegistered.value(0).toInt() - 1;
                }
            }
            else
            {
                qDebug() << "fetchNumRegistered error on the" << tracker <<"-th project: "<< fetchNumRegistered.lastError();
                return fetchNumRegistered.lastError().number();
            }

            // As there may be more than one configurations per project, we need to do a seperate query :(
            QString fetchProjectConfigurationsQuery = "Select config_id, value from project_configurations where project_id=:pid";
            QSqlQuery fetchProjectConfiguration(this->db);
            fetchProjectConfiguration.prepare(fetchProjectConfigurationsQuery);
            fetchProjectConfiguration.bindValue(":pid",projectId);
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    QJsonObject projectConfig;
                    projectConfig["type"] = fetchProjectConfiguration.value(0).toInt() - 1;
                    projectConfig["value"] = fetchProjectConfiguration.value(1).toInt();
                    projectConfigs.append(projectConfig);
                }
                project["configurations"] = projectConfigs;
            }
            else
            {
                qDebug() << "fetchProject error on the" << tracker <<"-th project: "<< this->db.lastError();
                return this->db.lastError().number();
            }

            ++tracker;
            projectsReturned.append(project);
        }
    }
    else
    {
        qDebug() << "fetchAllProjects error:  "<< fetchAllProjects.lastError();
        return fetchAllProjects.lastError().number();
    }
    allProjectsReturns["projects"] = projectsReturned;
    allProjectsReturns["count"] = projectsReturned.count();
    return 0;
}

int ProjectRepository::fetchProjectForUser(QJsonObject& projectReturn, int projectId)
{
    QJsonArray projectArrayWithSingleProject;
    QString fetchProjectQuery = "Select p.project_id, p.project_title, p.project_description, c.config_id, c.value from project p where project_id=:pid";
    QSqlQuery fetchProject(this->db);
    fetchProject.prepare(fetchProjectQuery);
    fetchProject.bindValue(":pid",projectId);
    int tracker = 0;
    if(fetchProject.exec())
    {
        if(fetchProject.next())
        {
            QJsonObject project;
            QJsonArray projectConfigs;
            // Index
            //  0 -> project id
            //  1 -> project title
            //  2 -> project description

            QString projTitle = QString(fetchProject.value(1).toString());
            QString projDesc = QString(fetchProject.value(2).toString());

            project["title"] = projTitle;
            project["decription"] = projDesc;
            project["id"] = projectId;

            // Fetch the number of registered users in this project
            QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
            QSqlQuery fetchNumRegistered(this->db);
            fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
            fetchNumRegistered.bindValue(":pid",projectId);
            if(fetchNumRegistered.exec())
            {
                if(fetchNumRegistered.next())
                {
                    // Negate the AdministratorUser from the count
                    project["numberOfRegisteredUsers"] = fetchNumRegistered.value(0).toInt() - 1;
                }
            }
            else
            {
                qDebug() << "fetchNumRegistered error on the" << tracker <<"-th project: "<< fetchNumRegistered.lastError();
                return fetchNumRegistered.lastError().number();
            }


            // As there may be more than one configurations per project, we need to do a seperate query :(
            QString fetchProjectConfigurationsQuery = "Select config_id, value from project_configurations where project_id=:pid";
            QSqlQuery fetchProjectConfiguration(this->db);
            fetchProjectConfiguration.prepare(fetchProjectConfigurationsQuery);
            fetchProjectConfiguration.bindValue(":pid",projectId);
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    QJsonObject projectConfig;
                    projectConfig["type"] = fetchProjectConfiguration.value(0).toInt() - 1;
                    projectConfig["value"] = fetchProjectConfiguration.value(1).toInt();
                    projectConfigs.append(projectConfig);
                }
                project["configurations"] = projectConfigs;
            }
            else
            {
                qDebug() << "fetchProject error:  "<< this->db.lastError();
                return this->db.lastError().number();
            }
            projectArrayWithSingleProject.append(project);
            tracker++;
        }
    }
    else
    {
        qDebug() << "fetchProject error:  "<< fetchProject.lastError();
        return fetchProject.lastError().number();
    }
    projectReturn["projects"] = projectArrayWithSingleProject;
    projectReturn["count"] = projectArrayWithSingleProject.count();

    return 0;
}

int ProjectRepository::fetchProjectsForUser(QJsonObject& projectsForUser, int userId)
{
    QJsonArray projectsReturned;

    // Dump the projects that belong to a user
    QString fetchProjectsQuery = "Select p.project_id, p.project_title, p.project_description from project p join project_registration r on p.project_id=r.project_id where r.user_id=:uid";
    QSqlQuery fetchProject(this->db);
    fetchProject.prepare(fetchProjectsQuery);
    fetchProject.bindValue(":uid",userId);

    int tracker = 0;
    if(fetchProject.exec())
    {
        while(fetchProject.next())
        {
            // Indexes
            //  0 -> project_id
            //  1 -> project_title
            //  2 -> project_description
            QJsonObject project;
            QJsonArray projectConfigs;

            QString projectTitle = QString(fetchProject.value(1).toString());
            QString projectDescription = QString(fetchProject.value(2).toString());
            int projectId = fetchProject.value(0).toInt();
            project["id"] = projectId;
            project["title"] = projectTitle;
            project["description"] = projectDescription;

            // Fetch the number of registered users in this project
            QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
            QSqlQuery fetchNumRegistered(this->db);
            fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
            fetchNumRegistered.bindValue(":pid",projectId);
            if(fetchNumRegistered.exec())
            {
                if(fetchNumRegistered.next())
                {
                    // Negate 1 for the AdministratorUser
                    project["numberOfRegisteredUsers"] = fetchNumRegistered.value(0).toInt() - 1;
                }
            }
            else
            {
                qDebug() << "fetchNumRegistered error on the" << tracker <<"-th project: "<< fetchNumRegistered.lastError();
                return fetchNumRegistered.lastError().number();
            }

            // As there may be more than one configurations per project, we need to do a seperate query :(
            QString fetchProjectConfigurationsQuery = "Select config_id, value from project_configurations where project_id=:pid";
            QSqlQuery fetchProjectConfiguration(this->db);
            fetchProjectConfiguration.prepare(fetchProjectConfigurationsQuery);
            fetchProjectConfiguration.bindValue(":pid",projectId);
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    QJsonObject projectConfig;
                    projectConfig["type"] = fetchProjectConfiguration.value(0).toInt() - 1;
                    projectConfig["value"] = fetchProjectConfiguration.value(1).toInt();
                    projectConfigs.append(projectConfig);
                }
                project["configurations"] = projectConfigs;
            }
            else
            {
                qDebug() << "fetchProject error on the" << tracker <<"-th project: "<< this->db.lastError();
                return this->db.lastError().number();
            }

            ++tracker;
            projectsReturned.append(project);
        }
    }
    else
    {
        qDebug() << "fetchProject error:  "<< fetchProject.lastError();
        return fetchProject.lastError().number();
    }

    projectsForUser["projects"] = projectsReturned;
    projectsForUser["count"] = projectsReturned.count();

    return 0;
}

int ProjectRepository::userRegisteredInProject(int projectId, int userId)
{
    if(projectId <= 0)
    {
        // Something wrong probably happened when retreiving the project...
        return -1;
    }

    // Inserts a row in project_registration to show that this user is associated with that project
    QString registerUserQuery = "Insert into project_registration (project_id,user_id) values (:pid,:uid)";
    QSqlQuery registerUser(this->db);
    registerUser.prepare(registerUserQuery);
    registerUser.bindValue(":pid",projectId);
    registerUser.bindValue(":uid",userId);
    if(!registerUser.exec())
    {
        qDebug() << "registerUser error:  "<< registerUser.lastError();
        return registerUser.lastError().number();
    }

//    // Increment the number of students that are registered now that have just registered one
//    int currentRegisteredUsers = project.getNumberOfRegisteredUsers() + 1;
//    project.setNumberOfRegisteredUsers(currentRegisteredUsers);

    return 0;
}

int ProjectRepository::userUnregisteredFromProject(int projectId, int userId)
{
    if(projectId <= 0)
    {
        // Something wrong probably happened when retreiving the project...
        return -1;
    }


    // Delete a row in project_registration to show user had unregistered
    QString unRegisterUserQuery = "Delete from project_registration where project_id=:pid and user_id=:uid";
    QSqlQuery unRegisterUser(this->db);
    unRegisterUser.prepare(unRegisterUserQuery);
    unRegisterUser.bindValue(":pid",projectId);
    unRegisterUser.bindValue(":uid",userId);
    if(!unRegisterUser.exec())
    {
        qDebug() << "unRegisterUser error:  "<< unRegisterUser.lastError();
        return unRegisterUser.lastError().number();
    }

    // Decrement the number of students that are registered now that have just unregistered one
    // We know there is at least one user who is registered
//    int currentRegisteredUsers = project.getNumberOfRegisteredUsers() - 1;
//    project.setNumberOfRegisteredUsers(currentRegisteredUsers);

    return 0;
}

int ProjectRepository::fetchPPPsForProject(QJsonObject& pppsToReturn, int projectId)
{
    QJsonArray pppList;

    // Fetch the precomputed values then we are good.
    // Get the student user ids with their corresponding ppp_id
    QString fetchAllUsersRegisteredQuery = "Select u.username,u.user_id,u.ppp_id, u.lname,u.fname,p.ptscore,p.ttscore,p.web_bs from project_registration r join users u on u.ppp_id=r.ppp_id join ppp p on u.ppp_id=p.ppp_id where r.project_id=:pid and u.type=1";
    QSqlQuery fetchUsersRegistered(this->db);
    fetchUsersRegistered.prepare(fetchAllUsersRegisteredQuery);
    fetchUsersRegistered.bindValue(":pid",projectId);
    if(fetchUsersRegistered.exec())
    {
       while(fetchUsersRegistered.next())
       {
           QJsonObject ppp;
           QJsonObject student;
           // Index
           //  0 -> username
           //  1 -> user_id
           //  2 -> ppp_id
           //  3 -> lname
           //  4 -> fname
           //  5 -> personal tech score
           //  6 -> teammate tech score
           //  7 -> work ethic char

           QString fname = QString(fetchUsersRegistered.value(4).toString());
           QString lname = QString(fetchUsersRegistered.value(3).toString());
           int ppp_id = fetchUsersRegistered.value(2).toInt();
           int user_id = fetchUsersRegistered.value(1).toInt();
           QString username = QString(fetchUsersRegistered.value(0).toString());
           int personalScore = fetchUsersRegistered.value(5).toInt();
           int teammateScore = fetchUsersRegistered.value(6).toInt();
           unsigned char workEthic = (unsigned char)fetchUsersRegistered.value(7).toInt();

           // Build this student
           student["firstName"] = fname;
           student["lastName"] = lname;
           student["userName"] = username;
           student["id"] = user_id;

           // Build this Student's PPP
           ppp["pppID"] = ppp_id;
           ppp["personalTechnicalScore"] = personalScore;
           ppp["teammateTechnicalScore"] = teammateScore;
           ppp["workEthic"] = workEthic;
           ppp["user"] = student;

           pppList.append(ppp);


       }
    }
    else
    {
       qDebug() << "fetchUsersRegistered error:  "<< fetchUsersRegistered.lastError();
       return fetchUsersRegistered.lastError().number();
    }

    pppsToReturn["ppp"] = pppList;
    pppsToReturn["count"] = pppList.count();

    return 0;
}

