#include "projectlistwidget.h"
#include "projectcellwidget.h"

//  Subsystem dependencies
#include "DataAccessLayer/Models/cupidsession.h"
#include "Repository/storage.h"

#include <QDebug>

ProjectListWidget::ProjectListWidget(QWidget *parent) :
    QScrollArea(parent)
{
    projectCells = NULL;
    items = NULL;
    listSize = 0;
    listType = noList;
    this->setLayout(new QHBoxLayout);
    viewWillAppear();
}
ProjectListWidget::~ProjectListWidget()
{
    cleanUpList();
}

void ProjectListWidget::viewWillAppear()
{
    setUpList();
}

void ProjectListWidget::viewWillDisappear()
{
    listType = noList;
    cleanUpList();
}

void ProjectListWidget::cleanUpList()
{

    if(projectList.size() != 0)
    {
        Project *currentProjectInSession = CupidSession::getInstance()->getCurrentProject();
        for(int i = 0; i < listSize; i++)
        {
            if(currentProjectInSession != NULL && projectList[i] != currentProjectInSession)
                delete projectList[i];
        }
        projectList.clear();
    }

    if(projectCells != NULL)
    {
        listSize = projectList.size();
        for(int i = 0; i < listSize; i++)
        {
            items->layout()->removeWidget(projectCells[i]);
            delete projectCells[i];
        }
        delete items;
        delete [] projectCells;
        projectCells = NULL;
    }

}

void ProjectListWidget::setUpList()
{
    /* Clean up first */
    cleanUpList();


    if (listType != noList)
    {
        //TODO: Query DB here!!!
        User *currentUser = CupidSession::getInstance()->getCurrentUser();
        if(Storage::defaultStorage().executeActionForProject((listType == discoverProjectsList ? discoverProjects : fetchUsersProjects), *currentUser, projectList) != 0)
        {
            //ERROR:
            qDebug() << "Error occured on fetch";
        }
        else
        {
            displayList();
        }
    }
    else
    {
        //Should only be the case on first load by cuPID window.
    }
}

void ProjectListWidget::displayList()
{
    /*
     * creates a widget with all of the projects in it as projectCellWidgets
     */
    if (projectList.size() != 0)
    {
        listSize = projectList.size();
        projectCells = new ProjectCellWidget*[listSize];
        items = new QWidget;
        items->setLayout(new QFormLayout);
        this->setWidget(items);

        setWidgetResizable(true); //need this so the vertical scroll bar appears

        for(int i=0; i<listSize; i++)
        {
            ProjectCellWidget *cell = new ProjectCellWidget();
            cell->index = i;
            cell->getUi().lblTitle->setText(projectList[i]->getTitle());
            cell->getUi().lblDescription->setText(projectList[i]->getDescription());
            cell->getUi().lblNumRegistered->setText(QString::number(projectList[i]->getNumberOfRegisteredUsers()) + " Students Registered");
            QObject::connect(cell, SIGNAL(cellSelected(int)), this, SLOT(viewProjectSelected(int)));

            projectCells[i] = cell;
            items->layout()->addWidget(cell);
        }

    }

}

void ProjectListWidget::viewProjectSelected(int index)
{
    CupidSession::getInstance()->deleteCurrentProject();
    CupidSession::getInstance()->setCurrentProject(projectList[index]);
    emit userToViewProject();
    viewWillDisappear();
}

void ProjectListWidget::handleUserContextSwitch(DetailViewType type)
{
    if (type == DiscoverProjets)
    {
        //entering view
        this->listType = discoverProjectsList;
        viewWillAppear();
    }
    else if (type == MyProjects)
    {
        this->listType = myProjectsList;
        viewWillAppear();
    }
    else
    {
        //Leaving view
        viewWillDisappear();
    }
}
