#include "recentprojectswidget.h"
#include "ui_recentprojectswidget.h"
#include "errorcodes.h"

RecentProjectsWidget::RecentProjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecentProjectsWidget)
{
    ui->setupUi(this);

    //add buttons to array for easy iteration
    buttons.append(ui->btnRecent1);
    buttons.append(ui->btnRecent2);
    buttons.append(ui->btnRecent3);
}

RecentProjectsWidget::~RecentProjectsWidget()
{
    delete ui;
}

void RecentProjectsWidget::reloadRecentProjects()
{
    User *user = DataAccessFacade::managedDataAccess().getCurrentUser();

    if(projects.size() > 0)
    {
        int size = projects.size();
        foreach(Project *project, projects)
        {
            int index = projects.indexOf(project);
            projects.remove(index);
            DataAccessFacade::managedDataAccess().doneUsingProject(project);
        }
    }

    if(user != NULL)
    {
        if(DataAccessFacade::managedDataAccess().execute(fetchUserRecentProjects, *user, projects) == SUCCESS)
        {
            //Hide all buttons
            for(int i = 0; i < buttons.size(); i++)
            {
                buttons[i]->setText("");
                buttons[i]->hide();
            }

            for(int i = 0; i < projects.size(); i++)
            {
                QString text = projects[i]->getTitle();
                buttons[i]->setText(text);
                buttons[i]->setHidden(false);
            }
        }
        else
        {
            //TODO: ERROR occured
        }
    }
}

void RecentProjectsWidget::on_btnRecent1_clicked()
{
    DataAccessFacade::managedDataAccess().setCurrentProject(projects[0]);
    emit userToViewProject();
}

void RecentProjectsWidget::on_btnRecent2_clicked()
{
    DataAccessFacade::managedDataAccess().setCurrentProject(projects[1]);
    emit userToViewProject();
}

void RecentProjectsWidget::on_btnRecent3_clicked()
{
    DataAccessFacade::managedDataAccess().setCurrentProject(projects[2]);
    emit userToViewProject();
}
