#include "editteamconfigurationsdialog.h"
#include "ui_editteamconfigurationsdialog.h"

EditTeamConfigurationsDialog::EditTeamConfigurationsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeamConfigurationsDialog)
{
    ui->setupUi(this);

}

EditTeamConfigurationsDialog::~EditTeamConfigurationsDialog()
{
    delete ui;
}


Ui::EditTeamConfigurationsDialog&  EditTeamConfigurationsDialog::getUi()
{
    return *ui;
}
