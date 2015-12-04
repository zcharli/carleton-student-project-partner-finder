#include "cupidwindow.h"
#include "ui_cupidwindow.h"

// Subsystem dependencies
#include "DataAccessLayer/administratoruser.h"
#include "DataAccessLayer/studentuser.h"
#include "DataAccessLayer/dataaccessfacade.h"
#include "DataAccessLayer/qualification.h"
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

    //add recent projects to sidebar
    projectSidebar.getUI()->recentWidget->layout()->addWidget(&recentProjectsWidget);

    //adds all the main content to the main widget
    ui->mainContentStackedWidget->layout()->addWidget(&profileWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&projectsWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&settingsWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&createProjectWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&projectDetailsWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&homeWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&matchReport);
    ui->mainContentStackedWidget->setCurrentWidget(&homeWidget);

    //connects signals between sidebar and detail views
    QObject::connect(&projectSidebar, SIGNAL(profileClicked()),
                     this, SLOT(generateProfilePage()));
    QObject::connect(&projectSidebar, SIGNAL(logOutClicked()),
                     this, SLOT(logCurrentUserOut()));
    QObject::connect(&projectSidebar, SIGNAL(settingsClicked()),
                     this, SLOT(generateSettingsPage()));
    QObject::connect(&projectSidebar, SIGNAL(discoverProjectsClicked()),
                     this, SLOT(generateProjectsPage()));
    QObject::connect(&projectSidebar, SIGNAL(myProjectsClicked()),
                     this, SLOT(generateProjectsPage()));
    QObject::connect(&projectSidebar, SIGNAL(createProjectClicked()),
                     this, SLOT(generateCreateProjectPage()));
    QObject::connect(&projectSidebar, SIGNAL(homeClicked()),
                     this, SLOT(generateHomePage()));

    //Go through side bar as much as possible
    QObject::connect(&homeWidget, SIGNAL(managePPPClicked()),
                     &projectSidebar, SLOT(on_btnProfile_clicked()));
    QObject::connect(&homeWidget, SIGNAL(discoverProjectsClicked()),
                     &projectSidebar, SLOT(on_btnDiscoverProjects_clicked()));
    QObject::connect(&homeWidget, SIGNAL(editSettingsClicked()),
                     &projectSidebar, SLOT(on_btnSettings_clicked()));
    QObject::connect(&homeWidget, SIGNAL(createProjectClicked()),
                     &projectSidebar, SLOT(on_btnCreateProject_clicked()));

    //setup context switch handlers
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &profileWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &projectsWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &settingsWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &createProjectWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectSidebar, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &projectDetailsWidget, SLOT(handleUserContextSwitch(DetailViewType)));
    QObject::connect(&projectDetailsWidget, SIGNAL(userToSwitchContextTo(DetailViewType)),
                     &matchReport, SLOT(handleUserContextSwitch(DetailViewType)));

    QObject::connect(&createProjectWidget, SIGNAL(createProjectSucceeded()),
                     this, SLOT(generateProjectDetailsPage()));
    QObject::connect(this, SIGNAL(userToViewProject()),
                     &projectDetailsWidget, SLOT(userToViewProject()));

    QObject::connect(&projectsWidget, SIGNAL(userToViewProject()), this, SLOT(generateProjectDetailsPage()));
    QObject::connect(this, SIGNAL(userToViewProject()), &projectDetailsWidget, SLOT(userToViewProject()));

    QObject::connect(&projectDetailsWidget, SIGNAL(startAlgoClicked()), this, SLOT(generateMatchReportSummary()));

}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);

    /*  configure Sidebar options based on user     */
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->lblUsername->setText(DataAccessFacade::managedDataAccess().getCurrentUser()->getFirstName() + " " +DataAccessFacade::managedDataAccess().getCurrentUser()->getLastName());

    //  check what kind of user we are
    if (dynamic_cast<AdministratorUser *>(DataAccessFacade::managedDataAccess().getCurrentUser()))
    {
        sideBarUi->btnDiscoverProjects->hide();
        sideBarUi->dividerDiscoverProject->hide();
        sideBarUi->btnProfile->hide();
        sideBarUi->dividerProfile->hide();
        homeWidget.setAdmin();
    }
    else if (dynamic_cast<StudentUser *>(DataAccessFacade::managedDataAccess().getCurrentUser()))
    {
        sideBarUi->btnCreateProject->hide();
        sideBarUi->dividerCreateProject->hide();
        homeWidget.setStudent();
    }

    // Inform RecentProjectsWidget to load recentProjects
    recentProjectsWidget.reloadRecentProjects();
}

void cuPIDWindow::viewWillDisappear()
{
    //DataAccessFacade::managedDataAccess().deleteCurrentUser();
    //DataAccessFacade::managedDataAccess().deleteCurrentProject();

    delete pppController;
    pppController = NULL;

    //show all hidden elements
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->btnDiscoverProjects->show();
    //sideBarUi->dividerDiscoverProject->show();
    sideBarUi->btnProfile->show();
    //sideBarUi->dividerProfile->show();
    sideBarUi->btnCreateProject->show();
    //sideBarUi->dividerCreateProject->show();

    ui->mainContentStackedWidget->setCurrentWidget(&homeWidget);
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

void cuPIDWindow::generateHomePage(){
    ui->mainContentStackedWidget->setCurrentWidget(&homeWidget);
}

void cuPIDWindow::generateSettingsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&settingsWidget);
}

void cuPIDWindow::generateProjectsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&projectsWidget);
}

void cuPIDWindow::generateCreateProjectPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&createProjectWidget);
}

void cuPIDWindow::generateProjectDetailsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&projectDetailsWidget);
    emit userToViewProject();
}

void cuPIDWindow::generateMatchReportSummary()
{
    ui->mainContentStackedWidget->setCurrentWidget(&matchReport);
}

cuPIDWindow::~cuPIDWindow()
{
    delete ui;
}
