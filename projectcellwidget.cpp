#include "projectcellwidget.h"


ProjectCellWidget::ProjectCellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectCellWidget)
{
    ui->setupUi(this);
    index = 0;
}

ProjectCellWidget::~ProjectCellWidget()
{
    delete ui;
}


Ui::ProjectCellWidget& ProjectCellWidget::getUi()
{
    return *ui;
}

void ProjectCellWidget::on_btnViewProject_clicked()
{
    emit cellSelected(index);
}
