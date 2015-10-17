#include "cupidwindow.h"
#include "ui_cupidwindow.h"

#define WINDOW_MAX_WIDTH 1000
#define WINDOW_MAX_HEIGHT 650
#define SIDE_BAR_MAX_WIDTH 200
#define MAIN_CONTENT_WIDGET_MAX_WIDTH 450

cuPIDWindow::cuPIDWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cuPIDWindow), currentUser(new QString())
{
    ui->setupUi(this);
}

void cuPIDWindow::viewWillAppear()
{
    this->setFixedSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    //ui->sideBar->setFixedWidth(SIDE_BAR_MAX_WIDTH);
    //ui->mainContentWidget->setFixedWidth(MAIN_CONTENT_WIDGET_MAX_WIDTH);
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
