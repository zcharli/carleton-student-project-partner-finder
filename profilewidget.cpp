#include "profilewidget.h"
#include "ui_profilewidget.h"

ProfileWidget::ProfileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileWidget)
{
    ui->setupUi(this);
}

ProfileWidget::~ProfileWidget()
{
    delete ui;
}
