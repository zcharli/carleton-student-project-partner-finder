#ifndef TEAMCELLWIDGET_H
#define TEAMCELLWIDGET_H

#include <QWidget>

class Team;
class ProjectPartnerProfile;
class QListWidgetItem;

namespace Ui {
class TeamCellWidget;
}

class TeamCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeamCellWidget(Team&,QWidget *parent = 0);
    ~TeamCellWidget();

private slots:
    void on_btnBack_clicked();

    void on_btnDetails_clicked();

private:
    Ui::TeamCellWidget *ui;
    QVector<ProjectPartnerProfile*>& profilesInTeam;
    Team& teamToParse;
    QListWidgetItem **widgetsToTrackForDeletion;
    QString teamTechScore;
    QString teamSatScore;
    QString teamNeedScore;
    void viewWillAppear();
};

#endif // TEAMCELLWIDGET_H
