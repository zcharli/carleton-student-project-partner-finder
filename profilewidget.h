#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>

namespace Ui {
class ProfileWidget;
}

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileWidget(QWidget *parent = 0);
    ~ProfileWidget();

private:
    Ui::ProfileWidget *ui;
};

#endif // PROFILEWIDGET_H
