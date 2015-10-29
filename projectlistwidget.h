#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H

#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QString>
#include "Models/project.h"

class ProjectListWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ProjectListWidget(QWidget *parent = 0);
    ~ProjectListWidget();
    int listSize;

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

private:
    /*
     * List of projects
     */
    Project** projectList;
    QWidget* items;
    QLabel** title;
    QLabel** desc;
    QLabel** numPPPs;
    QPushButton** btnViewProject;
    QFrame** f;
signals:

public slots:

};

#endif // PROJECTLISTWIDGET_H
