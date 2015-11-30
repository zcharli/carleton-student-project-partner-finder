#include "matchreportview.h"
#include "ui_matchreportview.h"

MatchReportView::MatchReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchReportView)
{
    ui->setupUi(this);
}

MatchReportView::~MatchReportView()
{
    delete ui;
}
