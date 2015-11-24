#ifndef EDITTEAMCONFIGURATIONSDIALOG_H
#define EDITTEAMCONFIGURATIONSDIALOG_H

#include "ui_editteamconfigurationsdialog.h"

#include <QDialog>

namespace Ui {
class EditTeamConfigurationsDialog;
}

class EditTeamConfigurationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTeamConfigurationsDialog(QWidget *parent = 0);
    ~EditTeamConfigurationsDialog();

    Ui::EditTeamConfigurationsDialog& getUi();

private:
    Ui::EditTeamConfigurationsDialog *ui;
};

#endif // EDITTEAMCONFIGURATIONSDIALOG_H
