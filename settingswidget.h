#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "sidebarwidget.h"

#include <QWidget>
#include <QColorDialog>
#include <QMainWindow>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();
    void changeStyleSheet();
    void sendAppWidget(QApplication *);
    void initiate();

public slots:
    /*! handle the user context switching from this widget to another   */
    void handleUserContextSwitch(DetailViewType);

private slots:
        void on_btnChangeSettings_clicked();
        void on_btnColorSelector_clicked();
        void on_fontComboBox_activated(const QString &arg1);

private:
    Ui::SettingsWidget *ui;
    QColor  selectedColor;
    QString selectedFont;
    QString fontColor;
    QString stylesheet;
    QString hoverColor;
    QString gradientStart;
    QString gradientEnd;
    QApplication* myApp;
};

#endif // SETTINGSWIDGET_H
