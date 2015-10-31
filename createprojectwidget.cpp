#include "createprojectwidget.h"
#include "ui_createprojectwidget.h"

CreateProjectWidget::CreateProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectWidget)
{
    ui->setupUi(this);

    ui->txtProjectDesc->setText("");
    ui->txtProjectTitle->setText("");
    ui->teamSizeSpinBox->setValue(0);

}

CreateProjectWidget::~CreateProjectWidget()
{
    delete ui;
}


void CreateProjectWidget::on_btnSave_clicked()
{
    emit saveChangesClicked();
}


