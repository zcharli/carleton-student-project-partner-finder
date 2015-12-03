#ifndef MATCHREPORTVIEW_H
#define MATCHREPORTVIEW_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include <QString>
#include "sidebarwidget.h"
#include "insomniamatchingalgorithm.h"
#include "teamcellwidget.h"
#include "DataAccessLayer/project.h"


namespace Ui {
class MatchReportView;
}

class MatchReportView : public QWidget
{
    Q_OBJECT

public:
    explicit MatchReportView(QWidget *parent = 0);
    ~MatchReportView();

    /*!
    *  @param: none
    *   @desc: all setup for this VC done here
    * @return: void
    */
    void viewWillAppear();

    /*!
    *  @param: none
    *   @desc: all clean up for this VC done here
    * @return: void
    */
    void viewWillDisappear();


signals:


private slots:
    void handleUserContextSwitch(DetailViewType);

private:
    Ui::MatchReportView *ui;
    InsomniaMatchingAlgorithm *matchingAlgorithm;
    Project* projectToMatch;
    QVector<Team*>* teamMatchList;
    TeamCellWidget** teamUiWidget;
    QToolBox teamAccordion;
    int teamSize;
    void cleanUpMatch();
    void setUpSummary();
    void displaySummary();
    QString getFormattedMemebersInTeam(Team&);
    QWidget* container;
};

#endif // MATCHREPORTVIEW_H
