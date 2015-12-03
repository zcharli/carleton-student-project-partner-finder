#ifndef TEAMCELLWIDGET_H
#define TEAMCELLWIDGET_H

#include <QWidget>
#include <QPair>
#include <QLabel>
#include <QTableWidgetItem>

#include "team.h"

class ProjectPartnerProfile;
class QListWidgetItem;
class QStringList;

namespace Ui {
class TeamCellWidget;
}

class TeamCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeamCellWidget(Team&,int,QWidget *parent = 0);
    ~TeamCellWidget();

private slots:
    void on_btnBack_clicked();

    void on_btnDetails_clicked();

private:
    Ui::TeamCellWidget *ui;
    QVector<ProjectPartnerProfile*>& profilesInTeam;
    QVector<QPair<LogType,QString> >& reasonsList;
    Team& teamToParse;
    QTableWidgetItem **studentUserTableWidgetItems;
    QTableWidgetItem **studentTechScoreTableWidgetItems;
    QListWidgetItem **summaryElementsToTrackForDeletion;
    QString teamTechScore;
    QString teamSatScore;
    QString teamNeedScore;
    QString teamNumberString;
    QString detailStackTitle;
    int teamNumber;
    int numberOfSummaryElements;
    void viewWillAppear();
    void prepareForDisplay();
    void evaluateSatificationColor(QLabel*);
    QString getReasonIcon(LogType);
};

#endif // TEAMCELLWIDGET_H
