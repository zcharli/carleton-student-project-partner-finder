#include "createprojectwidget.h"
#include "ui_createprojectwidget.h"
#include "Repository/storage.h"

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

void CreateProjectWidget::setUpNewProject()
{
    if(project != NULL)
    {
        delete project;
        project = NULL;
    }

    QString title = "";
    QString description = "";
    project = new Project(title, description);
}


void CreateProjectWidget::viewWillAppear()
{
    setUpNewProject();
}

void CreateProjectWidget::viewWillDisappear()
{
    if(profile != NULL)
    {
        delete profile;
        project = NULL;
    }
}

void CreateProjectWidget::saveNewProject()
{
    QString title = ui->txtProjectTitle->text();
    QString description = ui->txtProjectDesc->text();
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

    project->setTitle(title);
    project->setDescription(description);
    project->

}

CreateProjectWidget::~CreateProjectWidget()
{
    delete ui;
    if (project != NULL)
    {
        delte project;
        project = NULL
    }
}


void CreateProjectWidget::on_btnSave_clicked()
{
    saveNewProject();
}


