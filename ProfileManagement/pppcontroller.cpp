#include "pppcontroller.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QStringList>

//  Subsystem dependencies
#include "DataAccessLayer/dataaccessfacade.h"
#include "DataAccessLayer/studentuser.h"

PPPController::PPPController(ProfileWidget* profileView, QObject *parent) :
    QObject(parent)
{
    this->profile = NULL;
    this->profileView = profileView;

    QObject::connect(profileView, SIGNAL(userToEditPPP()), this, SLOT(editPPP()));
    QObject::connect(profileView, SIGNAL(userToSavePPP()), this, SLOT(savePPP()));
    QObject::connect(profileView, SIGNAL(userToCreatePPP()), this, SLOT(createPPP()));
    QObject::connect(profileView, SIGNAL(userToSubmitCodingQuestion()), this, SLOT(saveScoreForCodingQuestion()));
    QObject::connect(profileView, SIGNAL(userToLeavePPP()), this, SLOT(handleContexSwitchAwayFromView()));
    QObject::connect(profileView, SIGNAL(userToViewPPP()), this, SLOT(handleContextSwitchToView()));

    newUserAnsweredCodingQuestion = false;

    retrievePPP();
}

void PPPController::retrievePPP()
{
    profile = NULL;

    StudentUser *currentUser = (StudentUser*)DataAccessFacade::managedDataAccess().getCurrentUser();
    //try checking the session to see if the profile has been retrieved
    profile = currentUser->getProfile();
    if(!profile && ((StudentUser*)currentUser)->getFetchIDForPPP() != 0)
    {
        //User has a profile in the database so we need to fetch it.
        profile = DataAccessFacade::defaultProfile(*currentUser);
        profile->setPPPID(currentUser->getFetchIDForPPP());
        if(DataAccessFacade::managedDataAccess().execute(fetchPPP, *currentUser, *profile) != 0)
        {
            // Error occurred on retrieving PPP
            delete profile;
            profile = NULL;
            QMessageBox messageBox;
            messageBox.critical(0,"Error","An error occured while trying to fetch your profile");
            messageBox.setFixedSize(500,200);
        }
        else
        {
            //Success (but nobody cares)

        }
    }
    else
    {
        //  current user has no profile
    }


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

void PPPController::handleContextSwitchToView()
{
    retrievePPP();
}

void PPPController::handleContexSwitchAwayFromView()
{
    //Remove reference to current profile if any
    profile = NULL;
    profileView->setUpDefault();
    setupUIForState(NoProfile);
}

void PPPController::setupUIForState(ProfileState state)
{

    switch(state)
    {
    case Viewing:
        //choose which main view to display
        profileView->getUI().noProfileView->setHidden(true);
        profileView->getUI().myProfileWidget->setHidden(false);
        profileView->codingWidget.setHidden(true);

        //hide all other buttons except edit
        profileView->getUI().btnSave->setHidden(true);
        profileView->getUI().btnEditPPP->setHidden(false);
        profileView->getUI().btnCreatePPP->setHidden(true);
        profileView->getUI().btnSaveCoding->setHidden(true);

        populateProfileView();

        //disableAllInteractions
        enableInteractions(false);
        break;
    case Editing:
        //choose which main view to display
        profileView->getUI().noProfileView->setHidden(true);
        profileView->getUI().myProfileWidget->setHidden(false);
        profileView->codingWidget.setHidden(true);

        //hide all other buttons except save
        profileView->getUI().btnSave->setHidden(false);
        profileView->getUI().btnEditPPP->setHidden(true);
        profileView->getUI().btnCreatePPP->setHidden(true);
        profileView->getUI().btnSaveCoding->setHidden(true);

        populateProfileView();

        //disableAllInteractions
        enableInteractions(true);
        break;
    case NoProfile:
        //choose which main view to display
        profileView->getUI().noProfileView->setHidden(false);
        profileView->getUI().myProfileWidget->setHidden(true);
        profileView->codingWidget.setHidden(true);

        //hide all other buttons except save
        profileView->getUI().btnSave->setHidden(true);
        profileView->getUI().btnEditPPP->setHidden(true);
        profileView->getUI().btnCreatePPP->setHidden(false);
        profileView->getUI().btnSaveCoding->setHidden(true);

        //enableAllInteractions
        enableInteractions(true);
        break;
    case CodingQuestion:
        //choose which main view to display
        profileView->getUI().noProfileView->setHidden(true);
        profileView->getUI().myProfileWidget->setHidden(true);
        profileView->codingWidget.setHidden(false);

        //hide all other buttons except save
        profileView->getUI().btnSave->setHidden(true);
        profileView->getUI().btnEditPPP->setHidden(true);
        profileView->getUI().btnCreatePPP->setHidden(true);
        profileView->getUI().btnSaveCoding->setHidden(false);

        break;
    default:
        break;
    }

}

void PPPController::populateProfileView()
{
    if(profile && profile->getPPPID() != 0) //User has a valid PPP
    {
        //setup the profileView with PPP details
        profileView->getUI().spinUserCGPA->setValue(profile->getQualification(userCGPA).getValue()/(float)10);
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
    else
    {
        profileView->setUpDefault();
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
    profileView->enableDisableCheckBoxes();
}

void PPPController::editPPP()
{
    if (profile)
    {
        setupUIForState(Editing);
    }
    else
    {
        //  Don't know when this will be the case but it's good to check
        //TODO: NO PROFILE ERROR
        qDebug() <<"NO PROFILE FOR EDITING";
    }
}

void PPPController::savePPP()
{
    updatePPP();

    StudentUser *user = (StudentUser*)DataAccessFacade::managedDataAccess().getCurrentUser();



    if(profile->getPPPID() == 0)
    {
        if(!newUserAnsweredCodingQuestion)
        {
            setupUIForState(CodingQuestion);
            return;
        }
        //new PPP account
        if(DataAccessFacade::managedDataAccess().execute(createdPPP, *user, *profile) == 0)
        {
            // SAVE SUCCESSFUL Message
            QMessageBox messageBox;
            messageBox.information(0,"Success!","You can start registering your self to projects!");
            messageBox.setFixedSize(500,200);
            user->setFetchIDForPPP(profile->getPPPID());
            user->setProfile(profile);
        }
        else
        {
            // SAVE ERROR Message
            QMessageBox messageBox;
            messageBox.critical(0,"Error","An error occured while trying to create your profile :(");
            messageBox.setFixedSize(500,200);
        }
    }
    else
    {
        //updated PPP
        if(DataAccessFacade::managedDataAccess().execute(updatedPPP, *user, *profile) == 0)
        {
            // UPDATE SUCCESSFUL MESSAGE
            QMessageBox messageBox;
            messageBox.information(0,"Success","We've just successfully updated your profile!");
            messageBox.setFixedSize(500,200);
        }
        else
        {
            // UPDATE ERROR MESSAGE
            QMessageBox messageBox;
            messageBox.critical(0,"Error","An error occured while trying to update your profile :(");
            messageBox.setFixedSize(500,200);
        }

    }

    setupUIForState(Viewing);
}

void PPPController::createPPP()
{
    StudentUser *currentUser = (StudentUser *)DataAccessFacade::managedDataAccess().getCurrentUser();
    profile = DataAccessFacade::defaultProfile(*currentUser);

    setupUIForState(Editing);
}

void PPPController::processFinishedMarkingQuestion()
{
    if (timer != NULL && timer->isActive())
    {
        // Finished running before timer
        timer->stop();
        markingSuccessful = true;
    }

    if(markingSuccessful)
    {
        if(codeMarker->exitCode() == 0)
        {
            QString stdout = codeMarker->readAllStandardOutput();
            qDebug() << "stdout: " << stdout;

            float codingScore = stdout.toFloat();
            int numCorrect = profileView->codingWidget.getMultipleChoiceResults();
            qDebug() << codingScore;
            newUserAnsweredCodingQuestion = true;
            delete codeMarker;
            codeMarker = NULL;
            QMessageBox messageBox;
            QString scoreMessage = QString("Success! We just marked your submission.\n You scored: %1 out of 5 on the multiple choice questions \n %2 out of 100 in the coding.\nTHANKS!").
                    arg(QString::number(numCorrect),QString::number(codingScore));
            QMessageBox::critical(0,"Success!", scoreMessage);
            messageBox.setFixedSize(500,200);
            savePPP();
        }
        else
        {
            QMessageBox messageBox;
            messageBox.setFixedSize(500,200);
            QString stderr = codeMarker->readAllStandardError();
            QString errorMessage = "Error! We found the Following errors while trying to mark your code.\n Please resolve them and try again\n" + stderr;
            QMessageBox::critical(0,"Error!", errorMessage);
        }
    }
}

void PPPController::codingTimerFinished()
{
    delete timer;
    timer = NULL;

    if (codeMarker != NULL)
    {
        //code is still running so we terminate it
        markingSuccessful = false;
        codeMarker->terminate();

        // Code Took Too Long
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Your code took too long Please try one more time' :(");
        messageBox.setFixedSize(500,200);
    }
}


void PPPController::saveScoreForCodingQuestion(){
    if(profileView->codingWidget.checkAllQuestionsAnswered())
    {
         //First write user's answer to a file
        QString submissionFileName = "studentSubmission";
        QString filePath="./codeChecker/" + submissionFileName;
        QFile file( filePath );
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << profileView->codingWidget.getCodeTextFromTextView() << endl;
            qDebug() << "Submission Written to file";

            //  Setup timer for the code marking
            timer = new QTimer();
            timer->setSingleShot(true);
            QObject::connect(timer, SIGNAL(timeout()), this, SLOT(codingTimerFinished()));

            //  Run code checker on submission
            codeMarker = new QProcess();
            QObject::connect(codeMarker, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinishedMarkingQuestion()));
            QString programName = "codeChecker/codeChecker.sh";
            QStringList args = QStringList() << submissionFileName;
            qDebug() << args;
            codeMarker->start(programName, args);
            timer->start(5000);
        }
        else
        {
            //TODO: Error unable to write to file
            QMessageBox messageBox;
            messageBox.critical(0,"Error","We were unable to save your submission\n It seems like we need permission from you to do some file writing :)");
            messageBox.setFixedSize(500,200);
        }

    }
    else
    {
        // UPDATE ERROR MESSAGE
        QMessageBox messageBox;
        messageBox.critical(0,"Error","The Questions don't seem too bad..\n Please attempt all questions in order to save your profile' :(");
        messageBox.setFixedSize(500,200);
    }


}


void PPPController::updatePPP()
{
    if(profile)
    {
        //extract all updated values and modify the configurations
        profile->changeQualification(Qualification(userCGPA, (profileView->getUI().spinUserCGPA->value())*10)); //multiply by 10 because of the decimal
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
        int workEthics[NUMBER_OF_WORK_ETHICS_QUALIFICATIONS];
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
                isChecked = profileView->getUI().chkEfficient->isChecked();
                break;
            case humorBit:
                isChecked = profileView->getUI().chkHumour->isChecked();
                break;
            case impulsiveBit:
                isChecked = profileView->getUI().chkImpulsive->isChecked();
                break;
            case flexibleBit:
                isChecked = profileView->getUI().chkFlexible->isChecked();
                break;
            case hardworkingBit:
                isChecked = profileView->getUI().chkHardworking->isChecked();
                break;
            }

            workEthics[i] = isChecked ? 1 : 0;
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
        profile->changeQualification(Qualification(teamMateVersionControl, profileView->sliderTeammateVersionControl->getValue()));
        profile->changeQualification(Qualification(teamMateWebDevelopment, profileView->sliderTeammateWebDevelopment->getValue()));

        profile->updateProfileScores();
    }
}
