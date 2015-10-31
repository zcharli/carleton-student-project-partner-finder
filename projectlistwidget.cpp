#include "projectlistwidget.h"

ProjectListWidget::ProjectListWidget(QWidget *parent) :
    QScrollArea(parent)
{
    refreshList();
}
ProjectListWidget::~ProjectListWidget()
{
    for(int i=0; i<listSize; i++)
    {
        delete projectList[i];
        delete title[i];
        delete desc[i];
        delete numPPPs[i];
        delete btnViewProject[i];
        delete f[i];
    }
    delete [] projectList;
    delete [] title;
    delete [] desc;
    delete [] numPPPs;
    delete [] btnViewProject;
    delete [] f;
    delete items;
}

void ProjectListWidget::refreshList()
{
    /*
     * making dummy projects for a list while we wait for the database
     */
    listSize = 10;
    projectList = new Project*[listSize];
    title = new QLabel*[listSize];
    desc = new QLabel*[listSize];
    numPPPs = new QLabel*[listSize];
    btnViewProject = new QPushButton*[listSize];
    f = new QFrame*[listSize];

    QString c = "Project Title";
    QString d = "This is the project description, i'm just adding content so it will look better. Description Description Description Description Description Description Description Description Description Description";

    for(int i=0; i<listSize; i++)
    {
       projectList[i] = new Project(c, d);
    }
    /*
     * Calls displayList directly to show all projects
     */
    displayList();
}

void ProjectListWidget::displayList()
{
    /*
     * creates a widget with all of the projects in it as labels and a view project
     * button for each. adds that widget to the object (Scroll Area)
     */
    items = new QWidget;
    items->setLayout(new QVBoxLayout);
    setWidgetResizable(true); //need this so the vertical scroll bar appears

    for(int i=0; i<listSize; i++)
    {
        title[i] = new QLabel(projectList[i]->getTitle());
        title[i]->setFont(QFont("",20));

        numPPPs[i] = new QLabel(QString::number(projectList[i]->getNumberOfRegisteredUsers())+" Students Registered");
        numPPPs[i]->setAlignment(Qt::AlignRight);

        desc[i] = new QLabel(projectList[i]->getDescription());
        desc[i]->setWordWrap(true); //need this so the description will go to the next line if its too long

        btnViewProject[i] = new QPushButton("View Project");

        f[i] = new QFrame;
        f[i]->setFrameShape(QFrame::HLine); //horizontal line

        items->layout()->addWidget(numPPPs[i]);
        items->layout()->addWidget(title[i]);
        items->layout()->addWidget(desc[i]);
        items->layout()->addWidget(btnViewProject[i]);
        items->layout()->addWidget(f[i]);
    }
    this->setWidget(items);
    this->setLayout(new QHBoxLayout);

}

void ProjectListWidget::handleUserContextSwitch()
{

}
