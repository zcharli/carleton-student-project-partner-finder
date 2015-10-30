#include "pppcontroller.h"
#include "Models/cupidsession.h"
#include "Models/studentuser.h"


PPPController::PPPController(ProfileWidget* profileView, QObject *parent) :
    QObject(parent)
{
    this->profile = NULL;
    this->profileView = profileView;

    QObject::connect(profileView, SIGNAL(userToEditPPP()), this, SLOT(editPPP()));
    QObject::connect(profileView, SIGNAL(userToSavePPP()), this, SLOT(savePPP()));
    QObject::connect(profileView, SIGNAL(userToCreatePPP()), this, SLOT(createPPP()));

    didSetProfile();
}

void PPPController::didSetProfile()
{
    if (profile)
    {
        setupUIForState(Viewing);
    }
    else
    {
        setupUIForState(NoProfile);
    }

}

PPPController::~PPPController()
{

}

void PPPController::setupUIForState(ProfileState state)
{

    switch(state)
    {
        case Viewing:
            //choose which main view to display
            profileView->getUI().noProfileView->setHidden(true);
            profileView->getUI().myProfileWidget->setHidden(false);

            //disableAllInteractions
            enableInteractions(false);

            //hide all other buttons except edit
            profileView->getUI().btnSave->setHidden(true);
            profileView->getUI().btnEditPPP->setHidden(false);
            profileView->getUI().btnCreatePPP->setHidden(true);
            populateProfileView();
            break;
        case Editing:
            //choose which main view to display
            profileView->getUI().noProfileView->setHidden(true);
            profileView->getUI().myProfileWidget->setHidden(false);

            //enableAllInteractions
            enableInteractions(true);

            //hide all other buttons except save
            profileView->getUI().btnSave->setHidden(false);
            profileView->getUI().btnEditPPP->setHidden(true);
            profileView->getUI().btnCreatePPP->setHidden(true);
            populateProfileView();
            break;
        case NoProfile:
            //choose which main view to display
            profileView->getUI().noProfileView->setHidden(false);
            profileView->getUI().myProfileWidget->setHidden(true);

            //enableAllInteractions
            enableInteractions(true);

            //hide all other buttons except save
            profileView->getUI().btnSave->setHidden(true);
            profileView->getUI().btnEditPPP->setHidden(true);
            profileView->getUI().btnCreatePPP->setHidden(false);
            break;
        default:
            break;
    }

}

void PPPController::populateProfileView()
{
    if(profile)
    {
        //setup the profileView with PPP details
        profileView->getUI().spinUserCGPA->setValue(profile->getQualification(userCGPA).getValue());
        profileView->sliderUserOO->setValue(profile->getQualification(userOO).getValue());
        profileView->sliderUserUI->setValue(profile->getQualification(userUI).getValue());
        profileView->sliderUserScripting->setValue(profile->getQualification(userScripting).getValue());
        profileView->sliderUserDB->setValue(profile->getQualification(userDB).getValue());
        profileView->sliderUserDesignPatterns->setValue(profile->getQualification(userDesignPatterns).getValue());
        profileView->sliderUserDataStructures->setValue(profile->getQualification(userDataStructures).getValue());
        profileView->sliderUserComputerSecurity->setValue(profile->getQualification(userComputerSecurity).getValue());
        profileView->sliderUserSoftwareDocumentation->setValue(profile->getQualification(userSoftwareDocumentation).getValue());
        profileView->sliderUserNetworkComputing->setValue(profile->getQualification(userNetworkComputing).getValue());
        profileView->sliderUserVersionControl->setValue(profile->getQualification(userVersionControl).getValue());
        profileView->sliderUserWebDevelopment->setValue(profile->getQualification(userWebDevelopment).getValue());

        //loop over all 8 work ethic qualifications
        profileView->numBoxSelected = 0;
        for (int i = 0; i < NUMBER_OF_WORK_ETHICS_QUALIFICATIONS; i++)
        {
            QCheckBox *currentChkBox = NULL;
            bool isChecked = false;

            switch(i)
            {
                case dependableBit:
                    isChecked = profile->hasWorkEthic(dependableBit);
                    currentChkBox = profileView->getUI().chkDependable;
                    break;
                case organizedBit:
                    isChecked = profile->hasWorkEthic(organizedBit);
                    currentChkBox = profileView->getUI().chkOrganized;
                    break;
                case proactiveBit:
                    isChecked = profile->hasWorkEthic(proactiveBit);
                    currentChkBox = profileView->getUI().chkProactive;
                    break;
                case efficientBit:
                    isChecked = profile->hasWorkEthic(efficientBit);
                    currentChkBox = profileView->getUI().chkEfficient;
                    break;
                case humorBit:
                    isChecked = profile->hasWorkEthic(humorBit);
                    currentChkBox = profileView->getUI().chkHumour;
                    break;
                case impulsiveBit:
                    isChecked = profile->hasWorkEthic(impulsiveBit);
                    currentChkBox = profileView->getUI().chkImpulsive;
                    break;
                case flexibleBit:
                    isChecked = profile->hasWorkEthic(flexibleBit);
                    currentChkBox = profileView->getUI().chkFlexible;
                    break;
                case hardworkingBit:
                    isChecked = profile->hasWorkEthic(hardworkingBit);
                    currentChkBox = profileView->getUI().chkHardworking;
                    break;
            }

            currentChkBox->setChecked(isChecked);
            profileView->numBoxSelected += isChecked ? 1 : 0;
        }
        profileView->enableDisableCheckBoxes();

        profileView->sliderTeammateOO->setValue(profile->getQualification(teamMateOO).getValue());
        profileView->sliderTeammateUI->setValue(profile->getQualification(teamMateUI).getValue());
        profileView->sliderTeammateScripting->setValue(profile->getQualification(teamMateScripting).getValue());
        profileView->sliderTeammateDB->setValue(profile->getQualification(teamMateDB).getValue());
        profileView->sliderTeammateDesignPatterns->setValue(profile->getQualification(teamMateDesignPatterns).getValue());
        profileView->sliderTeammateDataStructures->setValue(profile->getQualification(teamMateDataStructures).getValue());
        profileView->sliderTeammateComputerSecurity->setValue(profile->getQualification(teamMateComputerSecurity).getValue());
        profileView->sliderTeammateSoftwareDocumentation->setValue(profile->getQualification(teamMateSoftwareDocumentation).getValue());
        profileView->sliderTeammateNetworkComputing->setValue(profile->getQualification(teamMateNetworkComputing).getValue());
        profileView->sliderTeammateVersionControl->setValue(profile->getQualification(teamMateVersionControl).getValue());
        profileView->sliderTeammateWebDevelopment->setValue(profile->getQualification(teamMateWebDevelopment).getValue());
    }
}

void PPPController::enableInteractions(bool shouldEnable)
{
    profileView->getUI().spinUserCGPA->setEnabled(shouldEnable);
    profileView->sliderUserOO->setEnabled(shouldEnable);
    profileView->sliderUserUI->setEnabled(shouldEnable);
    profileView->sliderUserScripting->setEnabled(shouldEnable);
    profileView->sliderUserDB->setEnabled(shouldEnable);
    profileView->sliderUserDesignPatterns->setEnabled(shouldEnable);
    profileView->sliderUserDataStructures->setEnabled(shouldEnable);
    profileView->sliderUserComputerSecurity->setEnabled(shouldEnable);
    profileView->sliderUserSoftwareDocumentation->setEnabled(shouldEnable);
    profileView->sliderUserNetworkComputing->setEnabled(shouldEnable);
    profileView->sliderUserVersionControl->setEnabled(shouldEnable);
    profileView->sliderUserWebDevelopment->setEnabled(shouldEnable);
    profileView->getUI().chkDependable->setEnabled(shouldEnable);
    profileView->getUI().chkOrganized->setEnabled(shouldEnable);
    profileView->getUI().chkProactive->setEnabled(shouldEnable);
    profileView->getUI().chkEfficient->setEnabled(shouldEnable);
    profileView->getUI().chkHumour->setEnabled(shouldEnable);
    profileView->getUI().chkImpulsive->setEnabled(shouldEnable);
    profileView->getUI().chkFlexible->setEnabled(shouldEnable);
    profileView->getUI().chkHardworking->setEnabled(shouldEnable);
    profileView->sliderTeammateOO->setEnabled(shouldEnable);
    profileView->sliderTeammateUI->setEnabled(shouldEnable);
    profileView->sliderTeammateScripting->setEnabled(shouldEnable);
    profileView->sliderTeammateDB->setEnabled(shouldEnable);
    profileView->sliderTeammateDesignPatterns->setEnabled(shouldEnable);
    profileView->sliderTeammateDataStructures->setEnabled(shouldEnable);
    profileView->sliderTeammateComputerSecurity->setEnabled(shouldEnable);
    profileView->sliderTeammateSoftwareDocumentation->setEnabled(shouldEnable);
    profileView->sliderTeammateNetworkComputing->setEnabled(shouldEnable);
    profileView->sliderTeammateVersionControl->setEnabled(shouldEnable);
    profileView->sliderTeammateWebDevelopment->setEnabled(shouldEnable);
}

void PPPController::editPPP()
{
    setupUIForState(Editing);
}

void PPPController::savePPP()
{
    //TODO: Save PPP here
    setupUIForState(Viewing);
}

void PPPController::createPPP()
{
    //TODO: Create empty profile here
    setupUIForState(Editing);
}


void PPPController::updatePPP()
{
    if(profile)
    {
        //extract all updated values and modify the configurations
        profile->changeQualification(Qualification(userCGPA, profileView->getUI().spinUserCGPA->value()));
        profile->changeQualification(Qualification(userOO, profileView->sliderUserOO->getValue()));
        profile->changeQualification(Qualification(userUI, profileView->sliderUserUI->getValue()));
        profile->changeQualification(Qualification(userScripting, profileView->sliderUserScripting->getValue()));
        profile->changeQualification(Qualification(userDB, profileView->sliderUserDB->getValue()));
        profile->changeQualification(Qualification(userDesignPatterns, profileView->sliderUserDesignPatterns->getValue()));
        profile->changeQualification(Qualification(userDataStructures, profileView->sliderUserDataStructures->getValue()));
        profile->changeQualification(Qualification(userComputerSecurity, profileView->sliderUserComputerSecurity->getValue()));
        profile->changeQualification(Qualification(userSoftwareDocumentation, profileView->sliderUserSoftwareDocumentation->getValue()));
        profile->changeQualification(Qualification(userNetworkComputing, profileView->sliderUserNetworkComputing->getValue()));
        profile->changeQualification(Qualification(userVersionControl, profileView->sliderUserVersionControl->getValue()));
        profile->changeQualification(Qualification(userWebDevelopment, profileView->sliderUserWebDevelopment->getValue()));

        //loop over all 8 work ethic qualifications
        bool workEthics[NUMBER_OF_WORK_ETHICS_QUALIFICATIONS];
        for (int i = 0; i < NUMBER_OF_WORK_ETHICS_QUALIFICATIONS; i++)
        {
            bool isChecked = false;

            switch(i)
            {
                case dependableBit:
                    isChecked = profileView->getUI().chkDependable->isChecked();
                    break;
                case organizedBit:
                    isChecked = profileView->getUI().chkOrganized->isChecked();
                    break;
                case proactiveBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
                case efficientBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
                case humorBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
                case impulsiveBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
                case flexibleBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
                case hardworkingBit:
                    isChecked = profileView->getUI().chkProactive->isChecked();
                    break;
            }

            workEthics[i] = isChecked;
        }
        //create the workEthic qualification
        Qualification workEthicQualification = Qualification::WorkEthicQualificationFromMapping(workEthics);
        profile->changeQualification(workEthicQualification);

        profile->changeQualification(Qualification(teamMateOO, profileView->sliderTeammateOO->getValue()));
        profile->changeQualification(Qualification(teamMateUI, profileView->sliderTeammateUI->getValue()));
        profile->changeQualification(Qualification(teamMateScripting, profileView->sliderTeammateScripting->getValue()));
        profile->changeQualification(Qualification(teamMateDB, profileView->sliderTeammateDB->getValue()));
        profile->changeQualification(Qualification(teamMateDesignPatterns, profileView->sliderTeammateDesignPatterns->getValue()));
        profile->changeQualification(Qualification(teamMateDataStructures, profileView->sliderTeammateDataStructures->getValue()));
        profile->changeQualification(Qualification(teamMateComputerSecurity, profileView->sliderTeammateComputerSecurity->getValue()));
        profile->changeQualification(Qualification(teamMateSoftwareDocumentation, profileView->sliderTeammateSoftwareDocumentation->getValue()));
        profile->changeQualification(Qualification(teamMateNetworkComputing, profileView->sliderTeammateNetworkComputing->getValue()));
        profile->changeQualification(Qualification(teamMateWebDevelopment, profileView->sliderTeammateWebDevelopment->getValue()));

        //TODO: also save PPP here
    }
}
