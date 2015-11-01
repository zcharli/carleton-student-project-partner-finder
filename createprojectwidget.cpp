#include "createprojectwidget.h"
#include "ui_createprojectwidget.h"
#include "Repository/storage.h"
#include "Models/user.h"
#include "Models/cupidsession.h"
#include <QDebug>

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
        //TODO: Error user must fill in form to save
        return;
    }
    if (sizeConfiguration <= 1)
    {
        //TODO: Error Minimum size requirement is 2
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
        //TODO: Error occurred
        qDebug() << "Save failed";
        delete project;
        project = NULL;
    }
    else
    {
        //TODO: Save successfule
        //  Should transiotion user to viewing newly created Prject
        qDebug() << "Save Successful";
        CupidSession::getInstance()->setCurrentProject(project);
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

