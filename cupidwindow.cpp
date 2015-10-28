#include "cupidwindow.h"
#include "ui_cupidwindow.h"
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include <QLayout>

#define WINDOW_MAX_WIDTH 1000
#define WINDOW_MAX_HEIGHT 650

cuPIDWindow::cuPIDWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cuPIDWindow)
{
    ui->setupUi(this);

    // Initialize side bar widget (child of left pane)
    ui->sideBar->layout()->addWidget(&projectSidebar);
    projectSidebar.show();

    //adds all the main content to the main widget
    ui->mainContentStackedWidget->layout()->addWidget(&profileWidget);
    //connects the profile button to the generateProfile page method
    QObject::connect(&projectSidebar, SIGNAL(profileClicked()),
                     this, SLOT(generateProfilePage()));

}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    ui->textEdit->setText("<h1>Welcome " + currentUser->getUserName() + "</h1>");

    /*  configure Sidebar options based on user     */
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->lblUsername->setText(currentUser->getUserName());

    //  check what kind of user we are
    if (dynamic_cast<AdministratorUser *>(currentUser))
    {
        sideBarUi->btnDiscoverProject->hide();
        sideBarUi->dividerDiscoverProject->hide();
    }
    else if (dynamic_cast<StudentUser *>(currentUser))
    {
        sideBarUi->btnCreateProject->hide();
        sideBarUi->dividerCreateProject->hide();
    }
}

void cuPIDWindow::acceptUserLogin(User *user)
{
    show();
    currentUser = user;
    viewWillAppear();
}

void cuPIDWindow::generateProfilePage()
{
    //sets the current widget of maincontentStackedWidget to the profile widget
    ui->mainContentStackedWidget->setCurrentWidget(&profileWidget);
}
cuPIDWindow::~cuPIDWindow()
{
    delete ui;
}

