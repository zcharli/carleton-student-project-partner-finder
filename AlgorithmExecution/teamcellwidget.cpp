#include "teamcellwidget.h"
#include "ui_teamcellwidget.h"

#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QStringList>
#include <QSizePolicy>

#include "DataAccessLayer/projectpartnerprofile.h"

TeamCellWidget::TeamCellWidget(Team& teamToDisplay, int teamNumber, QWidget *parent) :
    QWidget(parent), profilesInTeam(teamToDisplay.getMembersInTeam()), teamNumber(teamNumber),
    reasonsList(teamToDisplay.getMatchSummaryForTeam()), teamToParse(teamToDisplay),
    ui(new Ui::TeamCellWidget)
{
    ui->setupUi(this);
    summaryElementsToTrackForDeletion = NULL;
    studentUserTableWidgetItems = NULL;
    studentTechScoreTableWidgetItems = NULL;
    ui->stackedWidget->setCurrentWidget(ui->MatchSummary);
    viewWillAppear();
}

TeamCellWidget::~TeamCellWidget()
{
    int i;
    if(studentUserTableWidgetItems != NULL)
    {
        for(i=0;i<profilesInTeam.size();++i)
        {
            delete studentUserTableWidgetItems[i];
            delete studentTechScoreTableWidgetItems[i];
        }
        delete [] studentUserTableWidgetItems;
        delete [] studentTechScoreTableWidgetItems;
        studentUserTableWidgetItems = NULL;
    }

    if(summaryElementsToTrackForDeletion != NULL)
    {
        for(i=0;i<numberOfSummaryElements;++i)
        {
            delete summaryElementsToTrackForDeletion[i];
        }
        delete [] summaryElementsToTrackForDeletion;
        summaryElementsToTrackForDeletion = NULL;
    }
    delete ui;
}

void TeamCellWidget::viewWillAppear()
{
    prepareForDisplay();
}

void TeamCellWidget::prepareForDisplay()
{
    if(profilesInTeam.size() > 0)
    {
        studentUserTableWidgetItems = new QTableWidgetItem*[profilesInTeam.size()];
        studentTechScoreTableWidgetItems = new QTableWidgetItem*[profilesInTeam.size()];
    }
    else
    {
        studentUserTableWidgetItems = NULL;
    }

    teamNumberString = "Team " + QString::number(teamNumber);
    teamTechScore = QString::number(teamToParse.getTeamTechScore());
    teamSatScore = QString::number(teamToParse.getTeamSatisfaction());
    teamNeedScore = QString::number(teamToParse.getTeamRequiredTeammateTechScore());
    detailStackTitle = "Detailed Match Report for " + teamNumberString;

    ui->lblDetailTitle->setText(detailStackTitle);
    ui->lblTeamNumber->setText(teamNumberString);
    ui->lblTeamScore->setText(teamTechScore);
    ui->lblSatisfiabilityScore->setText(teamSatScore);
    evaluateSatificationColor(ui->lblSatisfiabilityScore);
    ui->lblNumStudentsRegistered->setText(QString::number(profilesInTeam.size()));
    ui->lblTeamNeedScore->setText(teamNeedScore);
    ui->lblSummarySAT->setText(teamSatScore);
    evaluateSatificationColor(ui->lblSummarySAT);

    // Table settings for student names
    ui->tblRegisteredStudent->setColumnCount(2);
    ui->tblRegisteredStudent->setRowCount(profilesInTeam.size());
    ui->tblRegisteredStudent->horizontalHeader()->hide();
    ui->tblRegisteredStudent->verticalHeader()->hide();
    ui->tblRegisteredStudent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblRegisteredStudent->setShowGrid(false);

    int i;
    for(i=0;i<profilesInTeam.size();++i)
    {
        studentUserTableWidgetItems[i] = new QTableWidgetItem(QIcon(":/images/Images/User.png"),profilesInTeam.value(i)->getStudentUser().getUsernameIdentifer());
        //ui->lstStudentList->addItem(widgetsToTrackForDeletion[i]);
        ui->tblRegisteredStudent->setItem(i,0,studentUserTableWidgetItems[i]);

        studentTechScoreTableWidgetItems[i] = new QTableWidgetItem(profilesInTeam.value(i)->getTechnicalScores());
        ui->tblRegisteredStudent->setItem(i,1,studentTechScoreTableWidgetItems[i]);
    }

    numberOfSummaryElements = reasonsList.size();
    ui->lstMatchSummaryReasons->setWordWrap(true);
    if(numberOfSummaryElements > 0)
    {
        summaryElementsToTrackForDeletion = new QListWidgetItem*[numberOfSummaryElements];
    }

    for(i=0;i<numberOfSummaryElements;++i)
    {
        summaryElementsToTrackForDeletion[i] = new QListWidgetItem(QIcon(getReasonIcon(reasonsList[i].first)),reasonsList[i].second);
        ui->lstMatchSummaryReasons->addItem(summaryElementsToTrackForDeletion[i]);
    }
}

void TeamCellWidget::evaluateSatificationColor(QLabel* label)
{
    int satisfaction = teamToParse.getTeamSatisfaction();
    if(satisfaction < 0)
    {
        satisfaction *= -1;
    }

    if(satisfaction <= 10)
    {
        label->setStyleSheet("QLabel { color: #39b436; }");
    }
    else if (satisfaction <= 25)
    {
        label->setStyleSheet("QLabel { color: #f9f22b; }");
    }
    else
    {
        label->setStyleSheet("QLabel { color: #e41e22; }");
    }
}

QString TeamCellWidget::getReasonIcon(LogType type)
{
    switch(type)
    {
        case AddedStudent:
            return ":/images/Images/Add.png";
        case UnderSatisfied:
            return ":/images/Images/Under.png";
        case OverSatisfied:
            return ":/images/Images/Over.png";
        default:
            return ":/images/Images/None.png";
    }
}

void TeamCellWidget::on_btnBack_clicked()
{
    ui->btnBack->clearFocus();
    ui->stackedWidget->setCurrentWidget(ui->DetailedSummary);
}

void TeamCellWidget::on_btnDetails_clicked()
{
    ui->btnDetails->clearFocus();
    ui->stackedWidget->setCurrentWidget(ui->MatchSummary);
}
