#include "matchreportview.h"
#include "ui_matchreportview.h"
#include "DataAccessLayer/dataaccessfacade.h"

MatchReportView::MatchReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchReportView)
{
    ui->setupUi(this);
    //initiallizes the amount of teams created
    teamSize = 20;
    //sets the height of the full widget
    teamAccordion.setFixedHeight(50*teamSize);

    //initializes a cell widget
    teams = new TeamCellWidget*[teamSize];

    //goes through all teams and inserts a cell with the information provided

    for(int i=0; i < teamSize; i++){
        teams[i] = new TeamCellWidget(0, "Team Score","Students Registered", 5, "Rules and Description of Matching Process");
        teamAccordion.addItem(teams[i],"Team "+QString::number(i+1));
    }

    //sets the teamAccordion widget to be scrollable
    ui->scrollArea->setWidget(&teamAccordion);

    // Set up a empty report.
    viewWillAppear();
}

MatchReportView::~MatchReportView()
{
    for(int i=0; i < teamSize; i++){
        delete teams[i];
    }
    delete teams;
    delete ui;
}


void MatchReportView::viewWillAppear()
{
    projectToMatch = DataAccessFacade::managedDataAccess().getCurrentProject();

}

void MatchReportView::viewWillDisappear()
{
}

void MatchReportView::handleUserContextSwitch(DetailViewType type)
{
    if (type == MatchReport)
    {
        viewWillAppear();
    }
    else
    {
        viewWillDisappear();
    }
}
