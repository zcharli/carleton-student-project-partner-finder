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
    QString getLegendForSatisfactionLevel(QString satisfaction);
    QString teamTechScore;
    QString teamSatScore;
    QString teamNeedScore;
    QString teamNumberString;
    QString detailStackTitle;
    int teamNumber;
    int numberOfSummaryElements;

    /*!
    *  @param: satisfaction string: QString
    *   @desc: Prepares the satisfaction string for the given satisfaction level
    * @return: void
    */
    QString satisfactionTextForSatisfactionLevel(int);

    /*!
    *  @param: none
    *   @desc: Prepares the view to be displayed by allocating resources
    * @return: void
    */
    void viewWillAppear();

    /*!
    *  @param: none
    *   @desc: Set up the widgets needed to display a team summary report
    * @return: void
    */
    void prepareForDisplay();

    /*!
    *  @param: none
    *   @desc: Changes the color of a label based on the satisfaction rating
    * @return: void
    */
    void evaluateSatificationColor(QLabel*);

    /*!
    *  @param: logType: LogType
    *   @desc: Looks for the correct icon to place for algorithm log types
    * @return: QString
    */
    QString getReasonIcon(LogType);
};

#endif // TEAMCELLWIDGET_H
