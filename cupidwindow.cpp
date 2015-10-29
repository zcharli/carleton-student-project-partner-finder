#include "cupidwindow.h"
#include "ui_cupidwindow.h"
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include "Models/cupidsession.h"
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
    ui->mainContentStackedWidget->layout()->addWidget(&projectWidget);
    ui->mainContentStackedWidget->setCurrentWidget(&projectWidget);
    ui->mainContentStackedWidget->layout()->addWidget(&settingsWidget);

    //connects the profile button to the generateProfile page method
    QObject::connect(&projectSidebar, SIGNAL(profileClicked()),
                     this, SLOT(generateProfilePage()));
    QObject::connect(&projectSidebar, SIGNAL(logOutClicked()),
                     this, SLOT(logCurrentUserOut()));
    QObject::connect(&projectSidebar, SIGNAL(settingsClicked()),
                     this, SLOT(generateSettingsPage()));
}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    ui->textEdit->setText("<h1>Welcome " + CupidSession::getInstance()->getCurrentUser()->getUserName() + "</h1>");

    /*  configure Sidebar options based on user     */
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->lblUsername->setText(CupidSession::getInstance()->getCurrentUser()->getUserName());

    //  check what kind of user we are
    if (dynamic_cast<AdministratorUser *>(CupidSession::getInstance()->getCurrentUser()))
    {
        sideBarUi->btnDiscoverProject->hide();
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
    delete currentUser;

    //show all hidden elements
    Ui::SideBarWidget *sideBarUi = projectSidebar.getUI();
    sideBarUi->btnDiscoverProject->show();
    sideBarUi->dividerDiscoverProject->show();
    sideBarUi->btnProfile->show();
    sideBarUi->dividerProfile->show();
    sideBarUi->btnCreateProject->show();
    sideBarUi->dividerCreateProject->show();

    //TODO: restore user back to home screen.
}

void cuPIDWindow::acceptUserLogin(User *user)
{
    show();
    currentUser = user;
    viewWillAppear();
}

void cuPIDWindow::logCurrentUserOut()
{
    viewWillDisappear();
    hide();
    CupidSession::getInstance()->deleteCurrentUser();
    emit userLoggedOut();
}

void cuPIDWindow::generateProfilePage()
{
    //sets the current widget of maincontentStackedWidget to the profile widget
    ui->mainContentStackedWidget->setCurrentWidget(&profileWidget);
}

void cuPIDWindow::generateSettingsPage()
{
    ui->mainContentStackedWidget->setCurrentWidget(&settingsWidget);
}

cuPIDWindow::~cuPIDWindow()
{
    delete ui;
}
