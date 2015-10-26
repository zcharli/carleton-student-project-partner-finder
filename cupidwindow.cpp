#include "cupidwindow.h"
#include "ui_cupidwindow.h"
#include <QLayout>

#define WINDOW_MAX_WIDTH 1000
#define WINDOW_MAX_HEIGHT 650

cuPIDWindow::cuPIDWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cuPIDWindow), currentUser(new QString())
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
    ui->textEdit->setText("<h1>Welcome " + *currentUser + "</h1>");
    projectSidebar.setUsername(*currentUser);
}

void cuPIDWindow::acceptUserLogin(QString& user)
{
    show();
    *currentUser = user;
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

