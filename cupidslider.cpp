#include "cupidslider.h"

CupidSlider::CupidSlider(int minNum, int maxNum)
{
    /*
     * initiates the Slider
     */
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(minNum);
    slider->setMaximum(maxNum);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(1);

    /*
     * initiates the Labels
     */
    min = new QLabel(QString::number(minNum), this);
    max = new QLabel(QString::number(maxNum), this);

    /*
     * creates a layout and adds the slider in the middle and the labels aligned
     * left and right below the slider
     */
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(slider,0,0,1,3);
    min->setAlignment(Qt::AlignLeft);
    layout->addWidget(min,1,0,1,1);
    max->setAlignment(Qt::AlignRight);
    layout->addWidget(max,1,2,1,1);
    setLayout(layout);
}

CupidSlider::~CupidSlider(){
    delete slider;
    delete min;
    delete max;
}

int CupidSlider::getValue()
{
    return slider->value();
}

void CupidSlider::setValue(int newValue)
{
    slider->setValue(newValue);
}
