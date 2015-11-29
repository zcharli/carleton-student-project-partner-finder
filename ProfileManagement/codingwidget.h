#ifndef CODINGWIDGET_H
#define CODINGWIDGET_H

#include <QWidget>
#include "highlighter.h"
namespace Ui {
class CodingWidget;
}

class CodingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodingWidget(QWidget *parent = 0);
    ~CodingWidget();

private:
    Ui::CodingWidget *ui;
    Highlighter *highlighter;
    Highlighter *highlighter2;
};

#endif // CODINGWIDGET_H
