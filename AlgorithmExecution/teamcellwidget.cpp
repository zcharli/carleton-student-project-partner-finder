#include "teamcellwidget.h"
#include "ui_teamcellwidget.h"

TeamCellWidget::TeamCellWidget(QWidget *parent, QString score, QString students, int numStu, QString rules) :
    QWidget(parent),
    ui(new Ui::TeamCellWidget)
{
    ui->setupUi(this);

    ui->lblNumStudentsRegistered->setText(QString::number(numStu));
    ui->lblRules->setText(rules);
    ui->lblStudentsInTeam->setText(students);
    ui->lblTeamScore->setText(score);
}

TeamCellWidget::~TeamCellWidget()
{
    delete ui;
}

/*
 * Allows the user to go back to the match summary
 */
void TeamCellWidget::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->MatchSummary);
}

/*
 * Allows the user to go to the Detailed Summary
 */
void TeamCellWidget::on_btnDetails_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DetailedSummary);
}
