#include "cupidwindow.h"
#include "ui_cupidwindow.h"
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include "Models/cupidsession.h"
#include "Models/qualification.h"
#include <QLayout>

#define WINDOW_MAX_WIDTH 1000
#define WINDOW_MAX_HEIGHT 650

cuPIDWindow::cuPIDWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cuPIDWindow)
{
    ui->setupUi(this);

    pppController = NULL;

    // Initialize side bar widget (child of left pane)
    ui->sideBar->layout()->addWidget(&projectSidebar);
    projectSidebar.show();

    //adds all the main content to the main widget
    ui->mainContentStackedWidget->layout()->addWidget(&profileWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&discoverProjectsWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&settingsWidget);

    //connects signals between sidebar and detail views
    QObject::connect(&projectSidebar, SIGNAL(profileClicked()),
                     this, SLOT(generateProfilePage()));
    QObject::connect(&projectSidebar, SIGNAL(logOutClicked()),
                     this, SLOT(logCurrentUserOut()));
    QObject::connect(&projectSidebar, SIGNAL(settingsClicked()),
                     this, SLOT(generateSettingsPage()));
    QObject::connect(&projectSidebar, SIGNAL(discoverProjectsClicked()),
                     this, SLOT(generateDiscoverProjectsPage()));
    //setup context switch handlers
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &profileWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &discoverProjectsWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &settingsWidget, SLOT(handleUserContextSwitch(DetailViewType)));

}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    ui->txtWelcome->setText("<h1>Welcome " + CupidSession::getInstance()->getCurrentUser()->getUserName() + "</h1>");

    /*  configure Sidebar options based on user     */
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->lblUsername->setText(CupidSession::getInstance()->getCurrentUser()->getFirstName() + " " +CupidSession::getInstance()->getCurrentUser()->getLastName());

    //  check what kind of user we are
    if (dynamic_cast<AdministratorUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        sideBarUi->btnDiscoverProjects->hide();
        sideBarUi->dividerDiscoverProject->hide();
        sideBarUi->btnProfile->hide();
        sideBarUi->dividerProfile->hide();
    }
    else if (dynamic_cast<StudentUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        sideBarUi->btnCreateProject->hide();
        sideBarUi->dividerCreateProject->hide();
    }
}

void cuPIDWindow::viewWillDisappear()
{
    CupidSession::getInstance()->deleteCurrentUser();
    CupidSession::getInstance()->deleteCurrentProject();

    delete pppController;
    pppController = NULL;

    //show all hidden elements
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->btnDiscoverProjects->show();
    sideBarUi->dividerDiscoverProject->show();
    sideBarUi->btnProfile->show();
    sideBarUi->dividerProfile->show();
    sideBarUi->btnCreateProject->show();
    sideBarUi->dividerCreateProject->show();

    //TODO: restore user back to home screen.
    ui->txtWelcome->show();
}

void cuPIDWindow::acceptUserLogin()
{
    show();
    viewWillAppear();
}

void cuPIDWindow::logCurrentUserOut()
{
    viewWillDisappear();
    hide();
    emit userLoggedOut();
}

void cuPIDWindow::generateProfilePage()
{
    if (pppController == NULL)
    {
        pppController = new PPPController(&profileWidget);
    }
    //sets the current widget of maincontentStackedWidget to the profile widget
    ui->mainContentStackedWidget->setCurrentWidget(&profileWidget);
    profileWidget.viewWillAppear();
}

void cuPIDWindow::generateSettingsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&settingsWidget);
}

void cuPIDWindow::generateDiscoverProjectsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&discoverProjectsWidget);
}

cuPIDWindow::~cuPIDWindow()
{
    delete ui;
}
