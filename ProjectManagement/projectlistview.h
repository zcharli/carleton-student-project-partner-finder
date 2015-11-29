#ifndef PROJECTLISTVIEW_H
#define PROJECTLISTVIEW_H

#include "sidebarwidget.h"
#include "projectcellwidget.h"
#include "ProjectManagement/abstractprojectview.h"

//  Subsystem dependencies
#include "DataAccessLayer/project.h"

#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QString>
#include <QVector>

enum ListType
{
    discoverProjectsList = 0,
    myProjectsList,
    noList
};


class ProjectListView : public AbstractProjectView
{
    QScrollArea scrollArea;
    Q_OBJECT
public:
    explicit ProjectListView(QWidget *parent = 0);
    ~ProjectListView();
    int listSize;
    ListType listType;

    /*!
     *       @param: none
     *        @desc: gets the list of projects from the database
     *      @return: void
     */
    void refreshList();
    /*!
     *       @param: none
     *        @desc: adds all of the content of the projects
     *               to the widget
     *      @return: void
     */
    void displayList();

    void viewWillAppear();
    void viewWillDisappear();
    void cleanUpList();
    void setUpList();

signals:
    void userToViewProject();

private:
    /*
     * List of projects
     */
    QVector<Project*> projectList;
    ProjectCellWidget **projectCells;
    QWidget *items;

signals:

public slots:
    void handleUserContextSwitch(DetailViewType);
    void viewProjectSelected(int index);
};

#endif // PROJECTLISTVIEW_H
