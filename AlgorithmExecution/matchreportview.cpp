#include "matchreportview.h"
#include "ui_matchreportview.h"

#include "DataAccessLayer/dataaccessfacade.h"

#include <qdebug.h>
#include <QFormLayout>
#include <QVBoxLayout>

#define SUMMARY_WIDGET_HEIGHT 500

MatchReportView::MatchReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchReportView)
{
    ui->setupUi(this);
    this->teamMatchList = NULL;
    this->teamUiWidget = NULL;
    this->matchingAlgorithm = NULL;
    this->container = NULL;
}

MatchReportView::~MatchReportView()
{
    cleanUpMatch();
    delete ui;
}


void MatchReportView::viewWillAppear()
{
    cleanUpMatch();
    setUpSummary();
}

void MatchReportView::setUpSummary()
{
    projectToMatch = DataAccessFacade::managedDataAccess().getCurrentProject();
    teamMatchList = new QVector<Team*>();
    matchingAlgorithm = new InsomniaMatchingAlgorithm(projectToMatch);
    matchingAlgorithm->launch(*teamMatchList);

    //initiallizes the amount of teams created
    teamSize = teamMatchList->size();
    //sets the height of the full widget
    //teamAccordion.setFixedHeight(1310);

    //initializes a cell widget
    teamUiWidget = new TeamCellWidget*[teamSize];

    //goes through all teams and inserts a cell with the information provided
    displaySummary();

    //ui->scrollArea->setWidget(&teamAccordion);
}

void MatchReportView::displaySummary()
{
    if(teamSize > 0)
    {
        container = new QWidget();
        container->setLayout(new QVBoxLayout);
        ui->scrollArea->setWidget(container);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->clearFocus();
        for(int i=0; i < teamSize; i++)
        {
            //QString formatedMembersInTeam = getFormattedMemebersInTeam(*(teamMatchList->value(i)));
            teamUiWidget[i] = new TeamCellWidget(*(teamMatchList->value(i)), i+1,this);
            //teamAccordion.addItem();
            //teamAccordion.addItem(teamUiWidget[i],"Team "+QString::number(i+1));
            teamUiWidget[i]->setFixedHeight(SUMMARY_WIDGET_HEIGHT);
            container->layout()->addWidget(teamUiWidget[i]);
        }
    }
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
            container->layout()->removeWidget(teamUiWidget[i]);
            delete teamUiWidget[i];
        }
        delete container;
        delete [] teamUiWidget;
        teamUiWidget = NULL;
        container = NULL;
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

    if(container != NULL)
    {
//        for(i=0;i<teamSize;++i)
//        {

//        }
    }

    if(matchingAlgorithm != NULL)
    {
        delete matchingAlgorithm;
        matchingAlgorithm = NULL;
    }

    teamSize = 0;
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
