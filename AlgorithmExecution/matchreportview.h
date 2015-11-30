#ifndef MATCHREPORTVIEW_H
#define MATCHREPORTVIEW_H

#include <QWidget>

namespace Ui {
class MatchReportView;
}

class MatchReportView : public QWidget
{
    Q_OBJECT

public:
    explicit MatchReportView(QWidget *parent = 0);
    ~MatchReportView();

private:
    Ui::MatchReportView *ui;
};

#endif // MATCHREPORTVIEW_H
