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
    int getMultipleChoiceResults();
    int getCodingQuestionResult();

private:
    Ui::CodingWidget *ui;
    Highlighter *highlighter;
};

#endif // CODINGWIDGET_H
