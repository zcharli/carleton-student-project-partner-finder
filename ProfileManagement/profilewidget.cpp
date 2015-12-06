#include "profilewidget.h"
//  Subsystem dependencies
#include "DataAccessLayer/qualification.h"
#include <QDebug>
#define DEFAULT_VALUE 0

ProfileWidget::ProfileWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ProfileWidget)
{
    ui->setupUi(this);
    /*
     * Initiates User Sliders
     */
    sliderUserOO = new CupidSlider(1,10);
    sliderUserUI = new CupidSlider(1,10);
    sliderUserScripting = new CupidSlider(1,10);
    sliderUserDB = new CupidSlider(1,10);
    sliderUserDesignPatterns = new CupidSlider(1,10);
    sliderUserDataStructures = new CupidSlider(1,10);
    sliderUserComputerSecurity = new CupidSlider(1,10);
    sliderUserSoftwareDocumentation = new CupidSlider(1,10);
    sliderUserNetworkComputing = new CupidSlider(1,10);
    sliderUserVersionControl = new CupidSlider(1,10);
    sliderUserWebDevelopment= new CupidSlider(1,10);

    /*
     * Initiates Teammate Sliders
     */
    sliderTeammateOO = new CupidSlider(1,10);
    sliderTeammateUI = new CupidSlider(1,10);
    sliderTeammateScripting = new CupidSlider(1,10);
    sliderTeammateDB = new CupidSlider(1,10);
    sliderTeammateDesignPatterns = new CupidSlider(1,10);
    sliderTeammateDataStructures = new CupidSlider(1,10);
    sliderTeammateComputerSecurity = new CupidSlider(1,10);
    sliderTeammateSoftwareDocumentation = new CupidSlider(1,10);
    sliderTeammateNetworkComputing = new CupidSlider(1,10);
    sliderTeammateVersionControl = new CupidSlider(1,10);
    sliderTeammateWebDevelopment= new CupidSlider(1,10);

    /*
     * Adds the User Sliders to the Form Layout in the correct tab
     */
    ui->formLayout->addRow(new QLabel("Object Oriented\nProgramming Skills"), sliderUserOO);
    ui->formLayout->addRow(new QLabel("User Interface and\nUser Experience Skills"), sliderUserUI);
    ui->formLayout->addRow(new QLabel("Scripting Skills\n(any Language)"), sliderUserScripting);
    ui->formLayout->addRow(new QLabel("Database Design\nSkills"), sliderUserDB);
    ui->formLayout->addRow(new QLabel("System Modelling Patterns and\nArchitecture Design Skills"), sliderUserDesignPatterns);
    ui->formLayout->addRow(new QLabel("Familiarity With Data Structures and\nAlgorithms"), sliderUserDataStructures);
    ui->formLayout->addRow(new QLabel("Computer Security\nExperience"), sliderUserComputerSecurity);
    ui->formLayout->addRow(new QLabel("Software Documentation\nExpreience"), sliderUserSoftwareDocumentation);
    ui->formLayout->addRow(new QLabel("Computer Networking\nExperience"), sliderUserNetworkComputing);
    ui->formLayout->addRow(new QLabel("Version Control\nExperience"), sliderUserVersionControl);
    ui->formLayout->addRow(new QLabel("Web Development\nSkills"), sliderUserWebDevelopment);

    /*
     * Adds the TeammateLayout in the Form Layout in the correct tab
     */
    ui->formLayout_3->addRow(new QLabel("Object Oriented\nProgramming Skills"), sliderTeammateOO);
    ui->formLayout_3->addRow(new QLabel("User Interface and\nUser Experience Skills"), sliderTeammateUI);
    ui->formLayout_3->addRow(new QLabel("Scripting Skills\n(any Language)"), sliderTeammateScripting);
    ui->formLayout_3->addRow(new QLabel("Database Design\nSkills"), sliderTeammateDB);
    ui->formLayout_3->addRow(new QLabel("System Modelling Patterns and\nArchitecture Design Skills"), sliderTeammateDesignPatterns);
    ui->formLayout_3->addRow(new QLabel("Familiarity With Data Structures and\nAlgorithms"), sliderTeammateDataStructures);
    ui->formLayout_3->addRow(new QLabel("Computer Security\nExperience"), sliderTeammateComputerSecurity);
    ui->formLayout_3->addRow(new QLabel("Software Documentation\nExpreience"), sliderTeammateSoftwareDocumentation);
    ui->formLayout_3->addRow(new QLabel("Computer Networking\nExperience"), sliderTeammateNetworkComputing);
    ui->formLayout_3->addRow(new QLabel("Version Control\nExperience"), sliderTeammateVersionControl);
    ui->formLayout_3->addRow(new QLabel("Web Development\nSkills"), sliderTeammateWebDevelopment);
    numBoxSelected = 0;

    //Add coding question
    ui->codingQuestionView->addWidget(&codingWidget);
    viewWillAppear();
}


void ProfileWidget::viewWillAppear()
{
    //setup Profile for current Profile
    ui->chkDependable->setEnabled(false);
    ui->chkEfficient->setEnabled(false);
    ui->chkFlexible->setEnabled(false);
    ui->chkHardworking->setEnabled(false);
    ui->chkHumour->setEnabled(false);
    ui->chkImpulsive->setEnabled(false);
    ui->chkOrganized->setEnabled(false);
    ui->chkProactive->setEnabled(false);

}


void ProfileWidget::viewWillDisappear()
{
    //set all views to default state
    setUpDefault();
}

void ProfileWidget::setUpDefault()
{
    ui->spinUserCGPA->setValue(DEFAULT_VALUE);
    this->sliderUserOO->setValue(DEFAULT_VALUE);
    this->sliderUserUI->setValue(DEFAULT_VALUE);
    this->sliderUserScripting->setValue(DEFAULT_VALUE);
    this->sliderUserDB->setValue(DEFAULT_VALUE);
    this->sliderUserDesignPatterns->setValue(DEFAULT_VALUE);
    this->sliderUserDataStructures->setValue(DEFAULT_VALUE);
    this->sliderUserComputerSecurity->setValue(DEFAULT_VALUE);
    this->sliderUserSoftwareDocumentation->setValue(DEFAULT_VALUE);
    this->sliderUserNetworkComputing->setValue(DEFAULT_VALUE);
    this->sliderUserVersionControl->setValue(DEFAULT_VALUE);
    this->sliderUserWebDevelopment->setValue(DEFAULT_VALUE);

    //loop over all 8 work ethic qualifications
    this->numBoxSelected = 0;
    for (int i = 0; i < NUMBER_OF_WORK_ETHICS_QUALIFICATIONS; i++)
    {
        QCheckBox *currentChkBox = NULL;
        bool isChecked = false;

        switch(i)
        {
        case dependableBit:
            currentChkBox = ui->chkDependable;
            break;
        case organizedBit:
            currentChkBox = ui->chkOrganized;
            break;
        case proactiveBit:
            currentChkBox = ui->chkProactive;
            break;
        case efficientBit:
            currentChkBox = ui->chkEfficient;
            break;
        case humorBit:
            currentChkBox = ui->chkHumour;
            break;
        case impulsiveBit:
            currentChkBox = ui->chkImpulsive;
            break;
        case flexibleBit:
            currentChkBox = ui->chkFlexible;
            break;
        case hardworkingBit:
            currentChkBox = ui->chkHardworking;
            break;
        }

        currentChkBox->setChecked(isChecked);
    }

    this->sliderTeammateOO->setValue(DEFAULT_VALUE);
    this->sliderTeammateUI->setValue(DEFAULT_VALUE);
    this->sliderTeammateScripting->setValue(DEFAULT_VALUE);
    this->sliderTeammateDB->setValue(DEFAULT_VALUE);
    this->sliderTeammateDesignPatterns->setValue(DEFAULT_VALUE);
    this->sliderTeammateDataStructures->setValue(DEFAULT_VALUE);
    this->sliderTeammateComputerSecurity->setValue(DEFAULT_VALUE);
    this->sliderTeammateSoftwareDocumentation->setValue(DEFAULT_VALUE);
    this->sliderTeammateNetworkComputing->setValue(DEFAULT_VALUE);
    this->sliderTeammateVersionControl->setValue(DEFAULT_VALUE);
    this->sliderTeammateWebDevelopment->setValue(DEFAULT_VALUE);
}

ProfileWidget::~ProfileWidget()
{
    delete sliderUserOO;
    delete sliderUserUI;
    delete sliderUserScripting;
    delete sliderUserDB;
    delete sliderUserDesignPatterns;
    delete sliderUserDataStructures;
    delete sliderUserComputerSecurity;
    delete sliderUserSoftwareDocumentation;
    delete sliderUserNetworkComputing;
    delete sliderUserVersionControl;
    delete sliderUserWebDevelopment;
    delete sliderTeammateOO;
    delete sliderTeammateUI;
    delete sliderTeammateScripting;
    delete sliderTeammateDB;
    delete sliderTeammateDesignPatterns;
    delete sliderTeammateDataStructures;
    delete sliderTeammateComputerSecurity;
    delete sliderTeammateSoftwareDocumentation;
    delete sliderTeammateNetworkComputing;
    delete sliderTeammateVersionControl;
    delete sliderTeammateWebDevelopment;
    delete ui;
}

Ui::ProfileWidget& ProfileWidget::getUI()
{
    return *ui;
}

void ProfileWidget::on_chkHardworking_clicked()
{
    if(ui->chkHardworking->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();

}

void ProfileWidget::on_chkFlexible_clicked()
{
    if(ui->chkFlexible->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkImpulsive_clicked()
{
    if(ui->chkImpulsive->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkHumour_clicked()
{
    if(ui->chkHumour->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkEfficient_clicked()
{
    if(ui->chkEfficient->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkProactive_clicked()
{
    if(ui->chkProactive->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkOrganized_clicked()
{
    if(ui->chkOrganized->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::on_chkDependable_clicked()
{
    if(ui->chkDependable->isChecked())
        numBoxSelected++;
    else
        numBoxSelected--;
    enableDisableCheckBoxes();
}

void ProfileWidget::enableDisableCheckBoxes(){
    if(numBoxSelected >= 5){
        ui->chkDependable->setEnabled(ui->chkDependable->isChecked());
        ui->chkEfficient->setEnabled(ui->chkEfficient->isChecked());
        ui->chkFlexible->setEnabled(ui->chkFlexible->isChecked());
        ui->chkHardworking->setEnabled(ui->chkHardworking->isChecked());
        ui->chkHumour->setEnabled(ui->chkHumour->isChecked());
        ui->chkImpulsive->setEnabled(ui->chkImpulsive->isChecked());
        ui->chkOrganized->setEnabled(ui->chkOrganized->isChecked());
        ui->chkProactive->setEnabled(ui->chkProactive->isChecked());
    }
    else
    {
        ui->chkDependable->setEnabled(true);
        ui->chkEfficient->setEnabled(true);
        ui->chkFlexible->setEnabled(true);
        ui->chkHardworking->setEnabled(true);
        ui->chkHumour->setEnabled(true);
        ui->chkImpulsive->setEnabled(true);
        ui->chkOrganized->setEnabled(true);
        ui->chkProactive->setEnabled(true);
    }
}

void ProfileWidget::on_btnSave_clicked()
{
    emit userToSavePPP();
    ui->chkDependable->setEnabled(false);
    ui->chkEfficient->setEnabled(false);
    ui->chkFlexible->setEnabled(false);
    ui->chkHardworking->setEnabled(false);
    ui->chkHumour->setEnabled(false);
    ui->chkImpulsive->setEnabled(false);
    ui->chkOrganized->setEnabled(false);
    ui->chkProactive->setEnabled(false);
}

void ProfileWidget::on_btnEditPPP_clicked()
{
    emit userToEditPPP();
    enableDisableCheckBoxes();
}

void ProfileWidget::on_btnCreatePPP_clicked()
{
    emit userToCreatePPP();

}

void ProfileWidget::on_btnSaveCoding_clicked()
{

    qDebug() << "You Got " << codingWidget.getMultipleChoiceResults() << " out of 5";
    emit userToSubmitCodingQuestion();
}


void ProfileWidget::handleUserContextSwitch(DetailViewType type)
{
    if (type == Profile)
    {
        emit userToViewPPP();
        viewWillAppear();
    }
    else
    {
        emit userToLeavePPP();
        viewWillDisappear();
    }


}
