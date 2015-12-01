#ifndef MATCHREPORTVIEW_H
#define MATCHREPORTVIEW_H

#include <QWidget>
<<<<<<< HEAD
#include <QToolBox>
#include <QString>
#include "sidebarwidget.h"
#include "insomniamatchingalgorithm.h"
#include "teamcellwidget.h"
#include "DataAccessLayer/project.h"

=======
#include "sidebarwidget.h"
#include "insomniamatchingalgorithm.h"
>>>>>>> Created team UI classes

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
<<<<<<< HEAD
    QToolBox teamAccordion;
    TeamCellWidget** teams;
    int teamSize;
=======
>>>>>>> Created team UI classes

signals:


private slots:
    void handleUserContextSwitch(DetailViewType);
<<<<<<< HEAD

private:
    Ui::MatchReportView *ui;
    InsomniaMatchingAlgorithm matchingAlgorithm;
    Project* projectToMatch;
=======
    //void generateMatchReport();
    //void startAlgoClicked();

private:
    Ui::MatchReportView *ui;
    InsomniaMatchingAlgorithm *matchingAlgorithm;

>>>>>>> Created team UI classes

};

#endif // MATCHREPORTVIEW_H
