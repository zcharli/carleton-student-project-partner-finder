#ifndef PROJECTCELLWIDGET_H
#define PROJECTCELLWIDGET_H

#include "ui_projectcellwidget.h"

#include <QWidget>

namespace Ui {
class ProjectCellWidget;
}

class ProjectCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectCellWidget(QWidget *parent = 0);
    ~ProjectCellWidget();

    //should make this private later
    int index;

    Ui::ProjectCellWidget& getUi();

signals:
    void cellSelected(int);

private:
    Ui::ProjectCellWidget *ui;

public slots:
    void on_btnViewProject_clicked();
};

#endif // PROJECTCELLWIDGET_H
