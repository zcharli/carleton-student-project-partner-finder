#include "cupidslider.h"

CupidSlider::CupidSlider(int minNum, int maxNum)
{
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(minNum);
    slider->setMaximum(maxNum);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(1);
    min = new QLabel(QString::number(minNum), this);
    max = new QLabel(QString::number(maxNum), this);
    QGridLayout *layout = new QGridLayout;
               layout->addWidget(slider,0,0,1,3);
               min->setAlignment(Qt::AlignLeft);
               layout->addWidget(min,1,0,1,1);
               max->setAlignment(Qt::AlignRight);
               layout->addWidget(max,1,2,1,1);
               max->move(-100,100);
               setLayout(layout);
}
