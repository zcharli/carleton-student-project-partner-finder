#include "matchreportview.h"
#include "ui_matchreportview.h"
#include "DataAccessLayer/dataaccessfacade.h"

MatchReportView::MatchReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchReportView)
{
    ui->setupUi(this);;

    // Set up a empty report.
    viewWillAppear();
}

MatchReportView::~MatchReportView()
{
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
