#include "sidebarwidget.h"



SideBarWidget::SideBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBarWidget)
{
    ui->setupUi(this);


    viewWillAppear();

}

SideBarWidget::~SideBarWidget()
{
    delete ui;
}

void SideBarWidget::viewWillAppear()
{

}


Ui::SideBarWidget* SideBarWidget::getUI()
{
    return ui;
}


void SideBarWidget::on_btnProfile_clicked()
{
    emit userToSwitchContextTo(Profile);
    emit profileClicked();
}

void SideBarWidget::on_btnSettings_clicked()
{
    emit userToSwitchContextTo(Settings);
    emit settingsClicked();
}

void SideBarWidget::on_btnLogOut_clicked()
{
    emit userToSwitchContextTo(Logout);
    emit logOutClicked();
}

void SideBarWidget::on_btnDiscoverProjects_clicked()
{
    emit userToSwitchContextTo(DiscoverProjets);
    emit discoverProjectsClicked();
}
