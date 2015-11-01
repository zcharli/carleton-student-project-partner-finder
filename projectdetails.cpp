#include "projectdetails.h"
#include "ui_projectdetails.h"
#include "Models/cupidsession.h"
#include "Models/user.h"
#include <QPushButton>
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include "editteamconfigurationsdialog.h"
#include "Repository/storage.h"
#include <QDebug>

ProjectDetails::ProjectDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectDetails)
{
    ui->setupUi(this);
    this->project = NULL;

    // Retrieve the project data and populate them into the view
    viewWillAppear();

    // Flag to know if the currentUser is registered in this project
    isRegistered = false;
}

ProjectDetails::~ProjectDetails()
{
    delete ui;
}


void ProjectDetails::didSetProject()
{
    updateUI();
}

void ProjectDetails::updateUI()
{
    if(project != NULL)
    {
        // Fill the form with all information from project
        ui->txtProjDescription->setText(project->getDescription());
        ui->txtProjTitle->setText(project->getTitle());
        ui->lblRegisteredStudents->setText(QString::number(project->getNumberOfRegisteredUsers()) + " Students Registered in this Project");
    }
}

void ProjectDetails::viewWillAppear()
{
    //  check what kind of user we are and make the nessesary changes to the UI
    if (dynamic_cast<AdministratorUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        ui->btnRegistration->setHidden(true);
        ui->btnEditProject->setHidden(false);
        ui->btnStartAlgo->setHidden(false);
    }
    else if (dynamic_cast<StudentUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        ui->btnRegistration->setHidden(false);
        ui->btnEditProject->setHidden(true);
        ui->btnStartAlgo->setHidden(true);
        if(((StudentUser *)CupidSession::getInstance()->getCurrentUser())->isRegisteredInProject(project))
        {
            ui->btnRegistration->setText(tr("Unregister"));
            isRegistered = true;
        }
    }

    updateUI();
}

void ProjectDetails::viewWillDisappear()
{
    project = NULL;
}

void ProjectDetails::on_btnRegistration_clicked()
{
    StudentUser* stuUser = (StudentUser *)CupidSession::getInstance()->getCurrentUser();
    if(stuUser->getProfile() == NULL)
    {
        // Notify StudentUser that they don't have a PPP

        return;
    }
    if(isRegistered) {
        // Unregister this student
        project->unRegisterPPP(stuUser->getProfile());
        ui->btnRegistration->setText(tr("Register"));
        isRegistered = false;
    }
    else
    {
        project->registerPPP(stuUser->getProfile());
        ui->btnRegistration->setText(tr("Unregister"));
        isRegistered = true;
    }

    emit registrationClicked();
}



void ProjectDetails::userToViewProject()
{
    this->project = CupidSession::getInstance()->getCurrentProject();
    if(project != NULL)
        didSetProject();

    viewWillAppear();
}

void ProjectDetails::on_btnStartAlgo_clicked()
{
    // Start the matching algorithm
    emit startAlgoClicked();
}

void ProjectDetails::on_btnEditProject_clicked()
{
    EditTeamConfigurationsDialog dialog(this);
    dialog.getUi().teamSizeSpinBox->setValue(project->getProjectConfiguration(TeamSize).getValue());
    dialog.exec();
    if(dialog.result() == QDialog::Accepted)
    {
        int newTeamConfiguration =  dialog.getUi().teamSizeSpinBox->value();
        QVector<Project*> projects;
        projects.append(project);

        //Save Configurations
        if(Storage::defaultStorage().executeActionForProject(updatedProject, *(CupidSession::getInstance()->getCurrentUser()), projects) != 0)
        {
            //TODO: update error
            qDebug() << "Error occured on update" + project->getProjectId();
        }
        else
        {
            //TODO: notify update succeeded
        }
    }
    //QObject::connect(&dialog, SIGNAL(accepted(), this, SLOT(configurationsUpdated())));
}

void ProjectDetails::handleUserContextSwitch(DetailViewType type)
{
    if (type == ProjectDetailType)
    {
        //entering view
        viewWillAppear();
    }
    else
    {
        //leaving view
        viewWillDisappear();
    }
}
