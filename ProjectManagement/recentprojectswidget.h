#ifndef RECENTPROJECTSWIDGET_H
#define RECENTPROJECTSWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>


#include "DataAccessLayer/dataaccessfacade.h"
#include "DataAccessLayer/project.h"

namespace Ui {
class RecentProjectsWidget;
}

class RecentProjectsWidget : public QWidget
{
    Q_OBJECT
    QVector<Project*> projects;
    QVector<QPushButton*> buttons;

public:
    explicit RecentProjectsWidget(QWidget *parent = 0);
    ~RecentProjectsWidget();

    void reloadRecentProjects();

private:
    Ui::RecentProjectsWidget *ui;

public slots:
    void on_btnRecent1_clicked();
    void on_btnRecent2_clicked();
    void on_btnRecent3_clicked();
};

#endif // RECENTPROJECTSWIDGET_H
