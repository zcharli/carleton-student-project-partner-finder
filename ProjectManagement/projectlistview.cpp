#include "projectlistview.h"
#include "projectcellwidget.h"

//  Subsystem dependencies
#include "DataAccessLayer/dataaccessfacade.h"

#include <QDebug>

ProjectListView::ProjectListView(QWidget *parent) :
    AbstractProjectView(parent)
{
    projectCells = NULL;
    items = NULL;
    listSize = 0;
    listType = noList;
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(&scrollArea);
    scrollArea.setLayout(new QHBoxLayout);
    viewWillAppear();
}
ProjectListView::~ProjectListView()
{
    cleanUpList();
}

void ProjectListView::viewWillAppear()
{
    setUpList();
}

void ProjectListView::viewWillDisappear()
{
    listType = noList;
    cleanUpList();
}

void ProjectListView::cleanUpList()
{

    if(projectList.size() != 0)
    {
        Project *currentProjectInSession = DataAccessFacade::managedDataAccess().getCurrentProject();
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

void ProjectListView::setUpList()
{
    /* Clean up first */
    cleanUpList();


    if (listType != noList)
    {
        //TODO: Query DB here!!!
        User *currentUser = DataAccessFacade::managedDataAccess().getCurrentUser();
        if(DataAccessFacade::managedDataAccess().execute((listType == discoverProjectsList ? discoverProjects : fetchUsersProjects), *currentUser, projectList) != 0)
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

void ProjectListView::displayList()
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
        scrollArea.setWidget(items);

        scrollArea.setWidgetResizable(true); //need this so the vertical scroll bar appears

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

void ProjectListView::viewProjectSelected(int index)
{
    DataAccessFacade::managedDataAccess().deleteCurrentProject();
    DataAccessFacade::managedDataAccess().setCurrentProject(projectList[index]);
    emit userToViewProject();
    viewWillDisappear();
}

void ProjectListView::handleUserContextSwitch(DetailViewType type)
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
