#include "projectrepository.h"
#include "userrepository.h"

// Subsystem dependencies
#include "DataAccessLayer/Models/project.h"
#include "DataAccessLayer/Models/user.h"
#include "DataAccessLayer/Models/projectpartnerprofile.h"
#include "DataAccessLayer/Models/qualification.h"
#include "DataAccessLayer/Models/studentuser.h"
#include "DataAccessLayer/Models/configuration.h"

#include <QSqlQuery>
#include <QVector>
#include "QDebug"
#include <QSqlError>

ProjectRepository::ProjectRepository(QSqlDatabase& db)
{
    this->db = db;
}

ProjectRepository::~ProjectRepository()
{}

int ProjectRepository::userCreatedProject(User &user, Project &project)
{
    // An Admin is "registered" to a project by the DB
    QString createProjectQuery = "Insert into project (project_title, project_description) values (:title,:desc)";
    QSqlQuery createProject(this->db);
    createProject.prepare(createProjectQuery);
    createProject.bindValue(":title", project.getTitle());
    createProject.bindValue(":desc",project.getDescription());

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

    project.setProjectId(projectID);
    qDebug() << "Project ID" + QString::number(project.getProjectId());

    // Insert configurations
    int i;
    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        if((int)project.getProjectConfiguration(i).getValue() != 0)
        {
            // Maybe not all configurations are set
            QString insertQualificationQuery = "Insert into project_configurations (config_id,project_id,value) values (:cid, :pid, :val)";
            QSqlQuery insertQualification(this->db);
            insertQualification.prepare(insertQualificationQuery);
            insertQualification.bindValue(":cid",(int)project.getProjectConfiguration(i).getType() + 1);
            insertQualification.bindValue(":pid", projectID);
            insertQualification.bindValue(":val",project.getProjectConfiguration(i).getValue());
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
    bindProjectToAdmin.bindValue(":uid",user.getUserId());
    if(!bindProjectToAdmin.exec())
    {
        qDebug() << "bindProjectToAdmin error:  "<< bindProjectToAdmin.lastError();
        return bindProjectToAdmin.lastError().number();
    }


    return 0;
}

int ProjectRepository::fetchProjectForUser(User &user, Project &project)
{
    // Just return one project for the user
    if(project.getProjectId() <= 0)
    {
        // This project hasnt been saved yet
        return -1;
    }
    QString fetchProjectQuery = "Select p.project_id, p.project_title, p.project_description, c.config_id, c.value from project p where project_id=:pid";
    QSqlQuery fetchProject(this->db);
    fetchProject.prepare(fetchProjectQuery);
    fetchProject.bindValue(":pid",project.getProjectId());
    if(fetchProject.exec())
    {
        if(fetchProject.next())
        {
            // Index
            //  0 -> project id
            //  1 -> project title
            //  2 -> project description

            project.setProjectId(fetchProject.value(0).toInt());
            QString projTitle = QString(fetchProject.value(1).toString());
            project.setTitle(projTitle);
            QString projDesc = QString(fetchProject.value(2).toString());
            project.setDescription(projDesc);

            // As there may be more than one configurations per project, we need to do a seperate query :(
            QString fetchProjectConfigurationsQuery = "Select config_id, value from project_configurations where project_id=:pid";
            QSqlQuery fetchProjectConfiguration(this->db);
            fetchProjectConfiguration.prepare(fetchProjectConfigurationsQuery);
            fetchProjectConfiguration.bindValue(":pid",project.getProjectId());
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    Configuration config(
                                (ConfigurationType)(fetchProjectConfiguration.value(0).toInt() - 1),
                                fetchProjectConfiguration.value(1).toInt());
                    project.changeConfiguration(config);
                }
            }
            else
            {
                qDebug() << "fetchProject error:  "<< this->db.lastError();
                return this->db.lastError().number();
            }
        }
    }
    else
    {
        qDebug() << "fetchProject error:  "<< fetchProject.lastError();
        return fetchProject.lastError().number();
    }

    // Grab the number of users who are registered in this project
    // This is only done because we lazy load the user PPPs into project
    QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
    QSqlQuery fetchNumRegistered(this->db);
    fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
    fetchNumRegistered.bindValue(":pid",project.getProjectId());
    if(fetchNumRegistered.exec())
    {
        if(fetchNumRegistered.next())
        {
            // Negate the AdministratorUser from the registration
            project.setNumberOfRegisteredUsers(fetchNumRegistered.value(0).toInt() - 1);
        }
    }
    else
    {
        qDebug() << "fetchNumRegistered error:  "<< fetchNumRegistered.lastError();
        return fetchNumRegistered.lastError().number();
    }

    return 0;
}

int ProjectRepository::userUpdatedProject(User &user, Project &project)
{
    // Update a project details and such
    if(project.getProjectId() <= 0)
    {
        // This project hasnt been saved yet
        return -1;
    }

    // Update the contents of a project
    QString updateProjQuery = "Update project set project_title=:title , project_description=:desc where project_id=:pid";
    QSqlQuery updateProject(this->db);
    updateProject.prepare(updateProjQuery);
    updateProject.bindValue(":title",project.getTitle());
    updateProject.bindValue(":desc",project.getDescription());
    updateProject.bindValue(":id",project.getProjectId());
    if(!updateProject.exec())
    {
        qDebug() << "updateProject error:  "<< updateProject.lastError();
        return updateProject.lastError().number();
    }

    // Update all configurations
    int i;
    for(i=0;i<NUMBER_OF_CONFIGURATIONS;++i)
    {
        if((int)project.getProjectConfiguration(i).getValue() != 0)
        {
            QString updateProjConfigQuery = "Update project_configurations set value=:val where config_id=:cid and project_id=:pid";
            QSqlQuery updateProjConfig(this->db);
            updateProjConfig.prepare(updateProjConfigQuery);
            updateProjConfig.bindValue(":val", project.getProjectConfiguration(i).getValue());
            updateProjConfig.bindValue(":cid",project.getProjectConfiguration(i).getType() + 1);
            updateProjConfig.bindValue(":pid",project.getProjectId());

            if(!updateProjConfig.exec())
            {
                qDebug() << "updateProjConfig error:  "<< this->db.lastError();
                return this->db.lastError().number();
            }
        }
    }

    return 0;
}

int ProjectRepository::fetchAllProjects(User &user, QVector<Project *>& projects)
{
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
            // Index
            //  0 -> project_id
            //  1 -> project_title
            //  2 -> project_description

            QString projectTitle = QString(fetchAllProjects.value(1).toString());
            QString projectDescription = QString(fetchAllProjects.value(2).toString());

            Project *projectListElement = new Project(projectTitle,projectDescription);
            projectListElement->setProjectId(fetchAllProjects.value(0).toInt());

            // Fetch the number of registered users in this project
            QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
            QSqlQuery fetchNumRegistered(this->db);
            fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
            fetchNumRegistered.bindValue(":pid",QString::number(projectListElement->getProjectId()));
            if(fetchNumRegistered.exec())
            {
                if(fetchNumRegistered.next())
                {
                    // Negate the AdministratorUser from the count
                    projectListElement->setNumberOfRegisteredUsers(fetchNumRegistered.value(0).toInt() - 1);
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
            fetchProjectConfiguration.bindValue(":pid",projectListElement->getProjectId());
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    Configuration config(
                                (ConfigurationType)(fetchProjectConfiguration.value(0).toInt() - 1),
                                fetchProjectConfiguration.value(1).toInt());
                    projectListElement->changeConfiguration(config);
                }
            }
            else
            {
                qDebug() << "fetchProject error on the" << tracker <<"-th project: "<< this->db.lastError();
                return this->db.lastError().number();
            }

            ++tracker;
            projects.append(projectListElement);
        }
    }
    else
    {
        qDebug() << "fetchAllProjects error:  "<< fetchAllProjects.lastError();
        return fetchAllProjects.lastError().number();
    }

    return 0;
}

int ProjectRepository::fetchProjectsForUser(User &user, QVector<Project *>& projects)
{
    // Dump the projects that belong to a user
    QString fetchProjectsQuery = "Select p.project_id, p.project_title, p.project_description from project p join project_registration r on p.project_id=r.project_id where r.user_id=:uid";
    QSqlQuery fetchProject(this->db);
    fetchProject.prepare(fetchProjectsQuery);
    fetchProject.bindValue(":uid",user.getUserId());
    int tracker = 0;
    if(fetchProject.exec())
    {
        while(fetchProject.next())
        {
            // Indexes
            //  0 -> project_id
            //  1 -> project_title
            //  2 -> project_description

            QString projectTitle = QString(fetchProject.value(1).toString());
            QString projectDescription = QString(fetchProject.value(2).toString());

            Project *projectListElement = new Project(projectTitle,projectDescription);
            projectListElement->setProjectId(fetchProject.value(0).toInt());

            // Fetch the number of registered users in this project
            QString fetchRegisteredUsersInProjectQuery = "Select count(user_id) from project_registration where project_id=:pid";
            QSqlQuery fetchNumRegistered(this->db);
            fetchNumRegistered.prepare(fetchRegisteredUsersInProjectQuery);
            fetchNumRegistered.bindValue(":pid",projectListElement->getProjectId());
            if(fetchNumRegistered.exec())
            {
                if(fetchNumRegistered.next())
                {
                    // Negate 1 for the AdministratorUser
                    projectListElement->setNumberOfRegisteredUsers(fetchNumRegistered.value(0).toInt() - 1);
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
            fetchProjectConfiguration.bindValue(":pid",projectListElement->getProjectId());
            if(fetchProjectConfiguration.exec())
            {
                while(fetchProjectConfiguration.next())
                {
                    Configuration config(
                                (ConfigurationType)(fetchProjectConfiguration.value(0).toInt() - 1),
                                fetchProjectConfiguration.value(1).toInt());
                    projectListElement->changeConfiguration(config);
                }
            }
            else
            {
                qDebug() << "fetchProject error on the" << tracker <<"-th project: "<< this->db.lastError();
                return this->db.lastError().number();
            }

            ++tracker;
            projects.append(projectListElement);
        }
    }
    else
    {
        qDebug() << "fetchProject error:  "<< fetchProject.lastError();
        return fetchProject.lastError().number();
    }

    return 0;
}

int ProjectRepository::userRegisteredInProject(User &user, Project &project)
{
    if(project.getProjectId() <= 0)
    {
        // Something wrong probably happened when retreiving the project...
        return -1;
    }

    // Inserts a row in project_registration to show that this user is associated with that project
    QString registerUserQuery = "Insert into project_registration (project_id,user_id) values (:pid,:uid)";
    QSqlQuery registerUser(this->db);
    registerUser.prepare(registerUserQuery);
    registerUser.bindValue(":pid",project.getProjectId());
    registerUser.bindValue(":uid",user.getUserId());
    if(!registerUser.exec())
    {
        qDebug() << "registerUser error:  "<< registerUser.lastError();
        return registerUser.lastError().number();
    }

    // Increment the number of students that are registered now that have just registered one
    int currentRegisteredUsers = project.getNumberOfRegisteredUsers() + 1;
    project.setNumberOfRegisteredUsers(currentRegisteredUsers);

    return 0;
}

int ProjectRepository::userUnregisteredFromProject(User &user, Project &project)
{
    if(project.getProjectId() <= 0 || project.getNumberOfRegisteredUsers() == 0)
    {
        // Something wrong probably happened when retreiving the project...
        return -1;
    }

    // Delete a row in project_registration to show user had unregistered
    QString unRegisterUserQuery = "Delete from project_registration where project_id=:pid and user_id=:uid";
    QSqlQuery unRegisterUser(this->db);
    unRegisterUser.prepare(unRegisterUserQuery);
    unRegisterUser.bindValue(":pid",project.getProjectId());
    unRegisterUser.bindValue(":uid",user.getUserId());
    if(!unRegisterUser.exec())
    {
        qDebug() << "unRegisterUser error:  "<< unRegisterUser.lastError();
        return unRegisterUser.lastError().number();
    }

    // Decrement the number of students that are registered now that have just unregistered one
    // We know there is at least one user who is registered
    int currentRegisteredUsers = project.getNumberOfRegisteredUsers() - 1;
    project.setNumberOfRegisteredUsers(currentRegisteredUsers);

    return 0;
}

int ProjectRepository::fetchPPPsForProject(User &user, Project &project)
{
    if(project.getProjectId() <= 0 || project.getNumberOfRegisteredUsers() == 0)
    {
        // Something wrong probably happened when retreiving the project...
        return -1;
    }

    // Fetch the precomputed values then we are good.
    // Get the student user ids with their corresponding ppp_id
    QString fetchAllUsersRegisteredQuery = "Select u.username,u.user_id,u.ppp_id, u.lname,u.fname,p.ptscore,p.ttscore,p.web_bs from project_registration r join users u on u.ppp_id=r.ppp_id join ppp p on u.ppp_id=p.ppp_id where r.project_id=:pid and u.type=1";
    QSqlQuery fetchUsersRegistered(this->db);
    fetchUsersRegistered.prepare(fetchAllUsersRegisteredQuery);
    fetchUsersRegistered.bindValue(":pid",project.getProjectId());
    if(fetchUsersRegistered.exec())
    {
       while(fetchUsersRegistered.next())
       {
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
           StudentUser *stuUser = new StudentUser(fname,lname,username,user_id);

           // Build this Student's PPP
           ProjectPartnerProfile *ppp = new ProjectPartnerProfile(*stuUser,personalScore,teammateScore,workEthic);
           project.addPPPtoProject(ppp);
           ppp->setPPPID(ppp_id);
       }
    }
    else
    {
       qDebug() << "fetchUsersRegistered error:  "<< fetchUsersRegistered.lastError();
       return fetchUsersRegistered.lastError().number();
    }

    return 0;
}
