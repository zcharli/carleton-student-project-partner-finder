#include "profilewidget.h"
#include "ui_profilewidget.h"

ProfileWidget::ProfileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileWidget)
{
    ui->setupUi(this);

    CupidSlider* sliderUserOO = new CupidSlider(1,10);
    CupidSlider* sliderUserUI = new CupidSlider(1,10);
    CupidSlider* sliderUserScripting = new CupidSlider(1,10);
    CupidSlider* sliderUserDB = new CupidSlider(1,10);
    CupidSlider* sliderUserDesignPatterns = new CupidSlider(1,10);
    CupidSlider* sliderUserDataStructures = new CupidSlider(1,10);

    CupidSlider* sliderTeammateOO = new CupidSlider(1,10);
    CupidSlider* sliderTeammateUI = new CupidSlider(1,10);
    CupidSlider* sliderTeammateScripting = new CupidSlider(1,10);
    CupidSlider* sliderTeammateDB = new CupidSlider(1,10);
    CupidSlider* sliderTeammateDesignPatterns = new CupidSlider(1,10);
    CupidSlider* sliderTeammateDataStructures = new CupidSlider(1,10);

    ui->formLayout->addRow(new QLabel("Object Oriented\nProficiency"), sliderUserOO);
    ui->formLayout->addRow(new QLabel("User Interface\nProficiency"), sliderUserUI);
    ui->formLayout->addRow(new QLabel("Scripting\nProficiency"), sliderUserDB);
    ui->formLayout->addRow(new QLabel("Database\nProficiency"), sliderUserScripting);
    ui->formLayout->addRow(new QLabel("Design Patterns\nand System architecture"), sliderUserDesignPatterns);
    ui->formLayout->addRow(new QLabel("Data Structures and\nAlgorithmsProficiency"), sliderUserDataStructures);

    ui->formLayout_3->addRow(new QLabel("Object Oriented\nProficiency"), sliderTeammateOO);
    ui->formLayout_3->addRow(new QLabel("User Interface\nProficiency"), sliderTeammateUI);
    ui->formLayout_3->addRow(new QLabel("Scripting\nProficiency"), sliderTeammateDB);
    ui->formLayout_3->addRow(new QLabel("Database\nProficiency"), sliderTeammateScripting);
    ui->formLayout_3->addRow(new QLabel("Design Patterns\nand System architecture"), sliderTeammateDesignPatterns);
    ui->formLayout_3->addRow(new QLabel("Data Structures and\nAlgorithmsProficiency"), sliderTeammateDataStructures);
}

ProfileWidget::~ProfileWidget()
{
    delete ui;
}
