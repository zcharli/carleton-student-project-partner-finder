#ifndef CUPIDSLIDER_H
#define CUPIDSLIDER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>

class CupidSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CupidSlider(int min, int max);
    QLabel* min;
    QLabel* max;
    QSlider* slider;

signals:

public slots:

};

#endif // CUPIDSLIDER_H
