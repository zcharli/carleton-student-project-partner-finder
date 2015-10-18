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
}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    ui->textEdit->setText("<h1>Welcome " + *currentUser + "</h1>");
}

void cuPIDWindow::acceptUserLogin(QString& user)
{
    show();
    *currentUser = user;
    viewWillAppear();
}

cuPIDWindow::~cuPIDWindow()
{
    delete ui;
}
