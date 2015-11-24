#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "sidebarwidget.h"

#include <QWidget>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

public slots:
    /*! handle the user context switching from this widget to another   */
    void handleUserContextSwitch(DetailViewType);

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
