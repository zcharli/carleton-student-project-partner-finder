#ifndef TEAMCELLWIDGET_H
#define TEAMCELLWIDGET_H

#include <QWidget>

namespace Ui {
class TeamCellWidget;
}

class TeamCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeamCellWidget(QWidget *parent = 0, QString score= "Team Score: 0", QString students = "Tommy Texter, Sassy Sally", int numStu = 0, QString rules = "No Rules");
    ~TeamCellWidget();

private slots:
    void on_btnBack_clicked();

    void on_btnDetails_clicked();

private:
    Ui::TeamCellWidget *ui;
};

#endif // TEAMCELLWIDGET_H
