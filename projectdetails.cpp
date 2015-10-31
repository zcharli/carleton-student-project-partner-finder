#include "projectdetails.h"
#include "ui_projectdetails.h"
#include "Models/cupidsession.h"
#include "Models/user.h"
#include <QPushButton>
#include "Models/administratoruser.h"
#include "Models/studentuser.h"

ProjectDetails::ProjectDetails(Project* project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectDetails)
{
    ui->setupUi(this);

    // The project that is passed to this view
    projectViewing = project;

    // Retrieve the project data and populate them into the view
    viewWillAppear();

    // Flag to know if the currentUser is registered in this project
    isRegistered = false;

    // Hook up these button handlers
    QObject::connect(ui->btnRegistration, &QPushButton::clicked, this, &ProjectDetails::on_btnRegistration_clicked);
    QObject::connect(ui->btnStartAlgo, &QPushButton::clicked, this, &ProjectDetails::on_btnStartAlgo_clicked);
}

ProjectDetails::~ProjectDetails()
{
    delete ui;
}

void ProjectDetails::viewWillAppear()
{
    // Fill the form with all
    ui->txtProjDescription->setText(projectViewing->getDescription());
    ui->txtProjTitle->setText(projectViewing->getTitle());

    //  check what kind of user we are and make the nessesary changes to the UI
    if (dynamic_cast<AdministratorUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        ui->btnRegistration->hide();
    }
    else if (dynamic_cast<StudentUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        ui->btnStartAlgo->hide();
        if(((StudentUser *)CupidSession::getInstance()->getCurrentUser())->isRegisteredInProject(projectViewing))
        {
            ui->btnRegistration->setText(tr("Unregister"));
            isRegistered = true;
        }
    }

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
        projectViewing->unRegisterPPP(stuUser->getProfile());
        ui->btnRegistration->setText(tr("Register"));
        isRegistered = false;
    }
    else
    {
        projectViewing->registerPPP(stuUser->getProfile());
        ui->btnRegistration->setText(tr("Unregister"));
        isRegistered = true;
    }

    emit registrationClicked();
}

void ProjectDetails::on_btnStartAlgo_clicked()
{
    // Start the matching algorithm
    emit startAlgoClicked();
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
    }
}
