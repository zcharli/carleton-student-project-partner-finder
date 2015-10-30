#include "profilewidget.h"
#include "ui_profilewidget.h"
#include "Models/qualification.h"

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
}

ProfileWidget::~ProfileWidget()
{
    delete ui;
}

void ProfileWidget::didSetProfile()
{
    ui->spinUserCGPA->setValue(profile->getQualification(userCGPA).getValue());
    sliderUserOO->setValue(profile->getQualification(userOO).getValue());
    sliderUserUI->setValue(profile->getQualification(userUI).getValue());
    sliderUserScripting->setValue(profile->getQualification(userScripting).getValue());
    sliderUserDB->setValue(profile->getQualification(userDB).getValue());
    sliderUserDesignPatterns->setValue(profile->getQualification(userDesignPatterns).getValue());
    sliderUserDataStructures->setValue(profile->getQualification(userDataStructures).getValue());
    sliderUserComputerSecurity->setValue(profile->getQualification(userComputerSecurity).getValue());
    sliderUserSoftwareDocumentation->setValue(profile->getQualification(userSoftwareDocumentation).getValue());
    sliderUserNetworkComputing->setValue(profile->getQualification(userNetworkComputing).getValue());
    sliderUserVersionControl->setValue(profile->getQualification(userVersionControl).getValue());
    sliderUserWebDevelopment->setValue(profile->getQualification(userWebDevelopment).getValue());

    //loop over all 8 work ethic qualifications
    for (int i = 0; i < 8; i++)
    {
        switch(i)
        {

        }
    }

    sliderTeammateOO->setValue(profile->getQualification(teamMateOO).getValue());
    sliderTeammateUI->setValue(profile->getQualification(teamMateUI).getValue());
    sliderTeammateScripting->setValue(profile->getQualification(teamMateScripting).getValue());
    sliderTeammateDB->setValue(profile->getQualification(teamMateDB).getValue());
    sliderTeammateDesignPatterns->setValue(profile->getQualification(teamMateDesignPatterns).getValue());
    sliderTeammateDataStructures->setValue(profile->getQualification(teamMateDataStructures).getValue());
    sliderTeammateComputerSecurity->setValue(profile->getQualification(teamMateComputerSecurity).getValue());
    sliderTeammateSoftwareDocumentation->setValue(profile->getQualification(teamMateSoftwareDocumentation).getValue());
    sliderTeammateNetworkComputing->setValue(profile->getQualification(teamMateNetworkComputing).getValue());
    sliderTeammateVersionControl->setValue(profile->getQualification(teamMateVersionControl).getValue());
    sliderTeammateWebDevelopment->setValue(profile->getQualification(teamMateWebDevelopment).getValue());
}

void ProfileWidget::setProfile(ProjectPartnerProfile *profile)
{
    this->profile = profile;
    didSetProfile();
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

void ProfileWidget::parseQualifications()
{

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

}
