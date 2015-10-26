#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

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

void SideBarWidget::setUsername(const QString strUsername)
{
    ui->lblUsername->setText(strUsername);
}

void SideBarWidget::on_btnProfile_clicked()
{
    emit profileClicked();
}
