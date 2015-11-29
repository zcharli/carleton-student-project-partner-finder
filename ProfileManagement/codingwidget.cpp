#include "codingwidget.h"
#include "ui_codingwidget.h"

CodingWidget::CodingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodingWidget)
{
    ui->setupUi(this);
    highlighter = new Highlighter(ui->txtEdit->document());
    highlighter2 = new Highlighter(ui->txtEdit2->document());
}

CodingWidget::~CodingWidget()
{
    delete ui;
}
