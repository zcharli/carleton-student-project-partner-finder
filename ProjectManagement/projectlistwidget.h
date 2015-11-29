#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H

#include "sidebarwidget.h"
#include "projectcellwidget.h"

//  Subsystem dependencies
#include "DataAccessLayer/project.h"

#include "abstractprojectview.h"

#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QString>
#include <QVector>

#include "abstractprojectview.h"

enum ListType
{
    discoverProjectsList = 0,
    myProjectsList,
    noList
};


class ProjectListWidget : public AbstractProjectView
{
    Q_OBJECT

    QScrollArea scrollArea;

public:
    explicit ProjectListWidget(QWidget *parent = 0);
    ~ProjectListWidget();
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

#endif // PROJECTLISTWIDGET_H
