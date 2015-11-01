#include "homewidget.h"
#include "ui_homewidget.h"

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
}

HomeWidget::~HomeWidget()
{
    delete ui;
}
void HomeWidget::setAdmin()
{
    ui->lblAdmin->setVisible(true);
    ui->lblStudent->setVisible(false);
    ui->btnCreateProject->setVisible(true);
    ui->btnDiscoverProjects->setVisible(false);
    ui->btnManageProjectPartnerProfile->setVisible(false);
}

void HomeWidget::setStudent()
{
    ui->lblAdmin->setVisible(false);
    ui->lblStudent->setVisible(true);
    ui->btnCreateProject->setVisible(false);
    ui->btnDiscoverProjects->setVisible(true);
    ui->btnManageProjectPartnerProfile->setVisible(true);
}

void HomeWidget::on_btnCreateProject_clicked()
{
    emit createProjectClicked();
}

void HomeWidget::on_btnDiscoverProjects_clicked()
{
    emit discoverProjectsClicked();
}

void HomeWidget::on_btnManageProjectPartnerProfile_clicked()
{
    emit managePPPClicked();
}

void HomeWidget::on_btnEditSettings_clicked()
{
    emit editSettingsClicked();
}
