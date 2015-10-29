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
    ~CupidSlider();

    /*!
     *       @param: none
     *        @desc: returns the value of the QSlider
     *      @return: int
     */
    int getValue();
private:
    /*
     * Labels for displaying the minimum value and maximum value under the slider
     */
    QLabel* min;
    QLabel* max;
    /*
     * Slider with chosen value
     */
    QSlider* slider;

signals:

public slots:

};

#endif // CUPIDSLIDER_H
