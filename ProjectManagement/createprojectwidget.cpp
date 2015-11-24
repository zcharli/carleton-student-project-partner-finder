#include "createprojectwidget.h"
#include "ui_createprojectwidget.h"

//  Subsystem dependencies
#include "Repository/storage.h"
#include "DataAccessLayer/user.h"
#include "DataAccessLayer/cupidsession.h"

#include <QDebug>
#include <QMessageBox>

CreateProjectWidget::CreateProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectWidget)
{
    ui->setupUi(this);

    ui->txtProjectDesc->setText("");
    ui->txtProjectTitle->setText("");
    ui->teamSizeSpinBox->setValue(0);

    project = NULL;
    viewWillAppear();
}


void CreateProjectWidget::viewWillAppear()
{
    ui->txtProjectTitle->setText("");
    ui->txtProjectDesc->setText("");
    ui->teamSizeSpinBox->setValue(0);
}

void CreateProjectWidget::viewWillDisappear()
{
    ui->txtProjectTitle->setText("");
    ui->txtProjectDesc->setText("");
    ui->teamSizeSpinBox->setValue(0);
    project = NULL;
}

void CreateProjectWidget::saveNewProject()
{
    QString title = ui->txtProjectTitle->text();
    QString description = ui->txtProjectDesc->toPlainText();
    int sizeConfiguration = ui->teamSizeSpinBox->value();

    if (title == "" || description == "")
    {
        // Error user must fill in form to save
        QMessageBox messageBox;
        messageBox.warning(0,"Incomplete","Please fill in the title and description before saving.");
        messageBox.setFixedSize(500,200);
        return;
    }
    if (sizeConfiguration <= 1)
    {
        // Error Minimum size requirement is 2
        QMessageBox messageBox;
        messageBox.warning(0,"Invalid Configuration","Team size configuration should be at least two.");
        messageBox.setFixedSize(500,200);
        return;
    }

    project = new Project(title, description);
    project->changeConfiguration(Configuration(TeamSize, sizeConfiguration));

    //Save project to database
    User *user = CupidSession::getInstance()->getCurrentUser();
    QVector<Project*> projects;
    projects.append(project);

    if (Storage::defaultStorage().executeActionForProject(createdProject, *user, projects) != 0)
    {
        // Error occurred
        qDebug() << "Save failed";
        delete project;
        project = NULL;
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error occured while attempting to fulfil your request.");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        // Save successfule
        //  Should transiotion user to viewing newly created Prject
        qDebug() << "Save Successful";
        CupidSession::getInstance()->setCurrentProject(project);
        QMessageBox messageBox;
        messageBox.information(0,"Success","Your project has been successfully created, students can now join");
        messageBox.setFixedSize(500,200);
        viewWillDisappear();
        emit createProjectSucceeded();
    }

}

CreateProjectWidget::~CreateProjectWidget()
{
    delete ui;
    if (project != NULL)
    {
        delete project;
        project = NULL;
    }
}

void CreateProjectWidget::on_btnSave_clicked()
{
    saveNewProject();
}


void CreateProjectWidget::handleUserContextSwitch(DetailViewType type)
{
    if (type == CreateProject)
    {
        viewWillAppear();
    }
    else
    {
        viewWillDisappear();
    }


}
