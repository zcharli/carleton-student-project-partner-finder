#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

SideBarWidget::SideBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBarWidget)
{
    ui->setupUi(this);
}

SideBarWidget::~SideBarWidget()
{
    delete ui;
}
