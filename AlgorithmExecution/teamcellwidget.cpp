#include "teamcellwidget.h"
#include "ui_teamcellwidget.h"

#include <QListWidgetItem>
#include "team.h"
#include "DataAccessLayer/projectpartnerprofile.h"

TeamCellWidget::TeamCellWidget(Team& teamToDisplay, QWidget *parent) :
    QWidget(parent), profilesInTeam(teamToDisplay.getMembersInTeam()), teamToParse(teamToDisplay),
    ui(new Ui::TeamCellWidget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->MatchSummary);
    viewWillAppear();
}

TeamCellWidget::~TeamCellWidget()
{
    if(widgetsToTrackForDeletion != NULL)
    {
        int i;
        for(i=0;i<profilesInTeam.size();++i)
        {
            delete widgetsToTrackForDeletion[i];
        }
        delete widgetsToTrackForDeletion;
    }
    delete ui;
}

void TeamCellWidget::viewWillAppear()
{
    if(profilesInTeam.size() > 0)
    {
        widgetsToTrackForDeletion = new QListWidgetItem*[profilesInTeam.size()];
    }
    else
    {
        widgetsToTrackForDeletion = NULL;
    }

    teamTechScore = QString::number(teamToParse.getTeamTechScore());
    teamSatScore = QString::number(teamToParse.getTeamSatisfaction());
    teamNeedScore = QString::number(teamToParse.getTeamRequiredTeammateTechScore());

    ui->lblTeamScore->setText(teamTechScore);
    ui->lblSatisfiabilityScore->setText(teamSatScore);
    ui->lblNumStudentsRegistered->setText(QString::number(profilesInTeam.size()));
    ui->lblTeamNeedScore->setText(teamNeedScore);
    int i;
    for(i=0;i<profilesInTeam.size();++i)
    {
        widgetsToTrackForDeletion[i] = new QListWidgetItem(QIcon("../cuPID/Images/User_Circle.png"),profilesInTeam.value(i)->getStudentUser().getUsernameIdentifer());
        ui->lstStudentList->addItem(widgetsToTrackForDeletion[i]);
    }
}

void TeamCellWidget::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DetailedSummary);
}

void TeamCellWidget::on_btnDetails_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->MatchSummary);
}
