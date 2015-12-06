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
    bool checkAllQuestionsAnswered();
    QString getCodeTextFromTextView();

    void viewWillAppear();

private:
    Ui::CodingWidget *ui;
    Highlighter *highlighter;
};

#endif // CODINGWIDGET_H
