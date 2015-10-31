#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}


void SettingsWidget::handleUserContextSwitch(DetailViewType type)
{
    if (type = Settings)
    {
        //entering view
    }
    else
    {
        //Leaving View
    }

}
