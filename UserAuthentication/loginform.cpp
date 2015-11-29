#include "loginform.h"
#include "ui_loginform.h"

//  Subsystem dependencies
#include "DataAccessLayer/administratoruser.h"
#include "DataAccessLayer/studentuser.h"
#include "DataAccessLayer/projectpartnerprofileproxy.h"
#include "AlgorithmExecution/insomniamatchingalgorithm.h"

#include "DataAccessLayer/dataaccessfacade.h"

#include <QMessageBox>
#include <QDebug>

#define PROG_BAR_DEFAULT_VALUE 0

#define DEBUG_USER "Leonidas"

/*  Generic Error Messages For the login Screen     */
#define INVALID_USERNAME_MESSAGE "Validation for specified Username failed. Please try again."
#define INCOMPLETE_INFORMATION_MESSAGE "Please fill out your user name to log in"
#define LOGIN_ERROR_MESSAGE "No user found with given user name. Please try again"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(ui->btnAdministrator, &QPushButton::clicked, this, &LoginForm::slotAdministratorUserLogin);
    connect(ui->btnStudent, &QPushButton::clicked, this, &LoginForm::slotStudentUserLogin);
    connect(ui->btnSignUp, &QPushButton::clicked, this, &LoginForm::slotCreateNewAccount);
    connect(&signUpForm, &SignUpForm::signUpAccepted, this, &LoginForm::signUpSucceeded);
    InsomniaMatchingAlgorithm algo;
    viewWillAppear();
}

void LoginForm::viewWillAppear()
{
    ui->eLabel->hide();
}

void LoginForm::viewWillDisappear()
{
    ui->eLabel->setText("");
    ui->txtLogin->setText("");
}


LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::getCurrentUserWithUserName(QString& username, UserType type, User **currentUser)
{
    QString firstname = "";
    QString  lastname = "";
    int            id = -1;

    //##########################################################################################################
    /*  Debug flow  Username: Leonidas will get you through login   */
    if(username.compare(QString(DEBUG_USER)) == 0)
    {
        // create debug firstname, lastname and id
        firstname = "Jack";
        lastname = "Brown";

        switch(type)
        {

            case Administrator:
                (*currentUser) = new AdministratorUser(firstname, lastname, username);
                break;
            case Student:
                (*currentUser) = new StudentUser(firstname, lastname, username);
                break;
        }

        // Add the current user to the session after successful login
        DataAccessFacade::managedDataAccess().setCurrentUser(*currentUser);

        return;
    }

    //##########################################################################################################

    if(username == "")
    {
        presentError(INCOMPLETE_INFORMATION_MESSAGE);
        return;
    } else
    {
        *currentUser = DataAccessFacade::defaultUser(type);

        /*  Query DB for user log in information   */
        if(DataAccessFacade::managedDataAccess().execute(login, **currentUser) != 0)
        {
            //error occured
            delete *currentUser;
            *currentUser = NULL;
            presentError(LOGIN_ERROR_MESSAGE);
            return;
        }
        else
        {
            if (dynamic_cast<StudentUser *>(*currentUser))
            {
                // Getting PPP data since its best to load up the user at start to avoid checks later
                //User has a profile in the database so we need to fetch it.
                if (((StudentUser *)*currentUser)->getFetchIDForPPP() != 0)
                {
                    ProjectPartnerProfile* profile = DataAccessFacade::defaultProfile(*((StudentUser*)*currentUser));
                    if(DataAccessFacade::managedDataAccess().execute(fetchPPP, *((StudentUser*)(*currentUser)), *((ProjectPartnerProfile*)profile)) != 0)
                    {
                        // Error occurred on retrieving PPP
                        delete *currentUser;
                        delete profile;
                        *currentUser = NULL;
                        profile = NULL;
                        QMessageBox messageBox;
                        messageBox.critical(0,"Error","An error occured while trying to fetch your profile");
                        messageBox.setFixedSize(500,200);
                        return;
                    }
                    else
                    {
                        //Success!!
                    }
                }
            }

            // Load the user up with the projects they have created/registered
            populateUserProjects(*currentUser);
        }

    }

    // Add the current user to the session after successful login
    DataAccessFacade::managedDataAccess().setCurrentUser(*currentUser);
}

void LoginForm::populateUserProjects(User *user)
{
    QVector<Project *> userProjects;
    if(DataAccessFacade::managedDataAccess().execute(fetchUsersProjects, *user, userProjects))
    {
        QMessageBox messageBox;
        messageBox.warning(0,"Error","Failed to retrieve Project information");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        //Extract ids and populate user's project id set
        for(int i = 0; i < userProjects.size(); i++)
        {
            user->addProjectToUser(userProjects[i]->getProjectId());
            delete userProjects[i];
        }
    }
}

void LoginForm::presentError(QString errorString)
{
    ui->eLabel->setText(errorString);
    ui->eLabel->show();
}

void LoginForm::signUpSucceeded(User *currentUser)
{
    QString username = currentUser->getUserName();
    UserType type = currentUser->getUserType();

    delete currentUser;
    currentUser = NULL;

    getCurrentUserWithUserName(username, type, &currentUser);

    if (currentUser != NULL)
    {
        emit loginAccepted();
        viewWillDisappear();
        close();
    }
    else
        presentError(QString(INVALID_USERNAME_MESSAGE));
}

void LoginForm::slotAdministratorUserLogin()
{
    QString username = ui->txtLogin->text();

    //Hide Error Message if it is showing
    ui->eLabel->hide();

    /*  Create User entity here
     *  We will need to fetch the information
     *  from the data base here
     */
    User *currentUser = NULL;
    getCurrentUserWithUserName(username, Administrator, &currentUser);
    if (currentUser != NULL)
    {
        emit loginAccepted();
        viewWillDisappear();
        close();
    }
    else
        presentError(QString(INVALID_USERNAME_MESSAGE));

}

void LoginForm::slotStudentUserLogin()
{
    QString username = ui->txtLogin->text();

    //Hide Error Message if it is showing
    ui->eLabel->hide();

    /*  Create User entity here
     *  We will need to fetch the information
     *  from the data base here
     */
    User *currentUser = NULL;
    getCurrentUserWithUserName(username, Student, &currentUser);

    if (currentUser != NULL)
    {
        emit loginAccepted();
        viewWillDisappear();
        close();
    }
    else
        presentError(QString(INVALID_USERNAME_MESSAGE));
}

void LoginForm::slotCreateNewAccount()
{
    hide();
    signUpForm.show();
}


void LoginForm::promptUserLogin()
{
    viewWillAppear();
    show();
}
