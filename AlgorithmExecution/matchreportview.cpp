#include "matchreportview.h"
#include "ui_matchreportview.h"
#include "DataAccessLayer/dataaccessfacade.h"

MatchReportView::MatchReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchReportView)
{
    ui->setupUi(this);
    this->teamMatchList = NULL;
    this->teamUiWidget = NULL;
    this->matchingAlgorithm = NULL;
}

MatchReportView::~MatchReportView()
{
    cleanUpMatch();
    delete ui;
}


void MatchReportView::viewWillAppear()
{
    projectToMatch = DataAccessFacade::managedDataAccess().getCurrentProject();
    teamMatchList = new QVector<Team*>();
    matchingAlgorithm = new InsomniaMatchingAlgorithm(projectToMatch);
    matchingAlgorithm->launch(*teamMatchList);

    //initiallizes the amount of teams created
    teamSize = teamMatchList->size();
    //sets the height of the full widget
    teamAccordion.setFixedHeight(50*teamSize);

    //initializes a cell widget
    teamUiWidget = new TeamCellWidget*[teamSize];

    //goes through all teams and inserts a cell with the information provided

    for(int i=0; i < teamSize; i++){
        teamUiWidget[i] = new TeamCellWidget(*(teamMatchList->value(i)));
        teamAccordion.addItem(teamUiWidget[i],"Team "+QString::number(i+1));
    }

    //sets the teamAccordion widget to be scrollable
    ui->scrollArea->setWidget(&teamAccordion);
}

void MatchReportView::viewWillDisappear()
{
    cleanUpMatch();
}

void MatchReportView::cleanUpMatch()
{
    int i;
    if(teamUiWidget != NULL)
    {
        for(i=0; i < teamSize; ++i){
            delete teamUiWidget[i];
        }
        delete teamUiWidget;
        teamUiWidget = NULL;
    }

    if(teamMatchList != NULL)
    {
        for(i=0;i<teamSize;++i)
        {
            delete teamMatchList->value(i);
        }
        delete teamMatchList;
        teamMatchList = NULL;
    }

    if(matchingAlgorithm != NULL)
    {
        delete matchingAlgorithm;
        matchingAlgorithm = NULL;
    }
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
