#include "settingswidget.h"
#include "ui_settingswidget.h"
#include <QFile>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

//opens stylesheet file and reads it into QString

    QFile file(":/style/Stylesheets/style.qss");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        stylesheet = QString(file.readAll());
        file.close();
    }
//initializes all the featured colors of the stylesheet and the Font
    hoverColor    = "#550000";
    gradientStart = "#840b11";
    gradientEnd   = "#c0010b";
    fontColor     = "white";
    selectedFont  = "Sans Serif";
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}


void SettingsWidget::handleUserContextSwitch(DetailViewType type)
{
    if (type == Settings)
    {
        //entering view
    }
    else
    {
        //Leaving View
    }

}

void SettingsWidget::on_btnChangeSettings_clicked()
{
    myApp->setStyleSheet(stylesheet.arg(gradientStart, gradientEnd, hoverColor,fontColor, selectedFont));
}


void SettingsWidget::on_btnColorSelector_clicked()
{
    selectedColor = QColorDialog::getColor();
//gets the lightness of the color selected
    int l = selectedColor.toHsl().lightness();

//checks if the lightness and sets the font color to white or black accordingly
    if (l<122)
        fontColor = "white";
    else
        fontColor = "black";
//takes the selected color and creates a gradient with a darker color and a hover color that is noticable
    gradientStart = selectedColor.darker(150).name();
    gradientEnd   = selectedColor.name();
    hoverColor    = selectedColor.darker(175).name();
}

void SettingsWidget::on_fontComboBox_activated(const QString &arg1)
{
    selectedFont = arg1;
}


void SettingsWidget::initiate()
{
    myApp->setStyleSheet(stylesheet.arg(gradientStart, gradientEnd, hoverColor,fontColor, selectedFont));
}


void SettingsWidget::sendAppWidget(QApplication *app){
    myApp = app;
}
