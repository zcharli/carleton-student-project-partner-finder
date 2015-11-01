#include "loginform.h"
#include <QDebug>
#include "ui_loginform.h"
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include "Models/cupidsession.h"
#include "Repository/storage.h"
#include <QMessageBox>

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

    viewWillAppear();
}

void LoginForm::viewWillAppear()
{
    ui->progBarLogin->hide();
    ui->eLabel->hide();
    ui->progBarLogin->setValue(PROG_BAR_DEFAULT_VALUE);
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
    QString firstname;
    QString lastname;
    int     id;

//##########################################################################################################
    /*  Debug flow  Username: Leonidas will get you through login   */
    if(username.compare(QString(DEBUG_USER)) == 0)
    {
        // create debug firstname, lastname and id
        firstname = "Jack";
        lastname = "Brown";
        id = 7;

        switch(type)
        {
            case Administrator:
                (*currentUser) = new AdministratorUser(firstname, lastname, username, id);
                break;
            case Student:
                (*currentUser) = new StudentUser(firstname, lastname, username, id);
                break;
        }

        // Add the current user to the session after successful login
        CupidSession::getInstance()->setCurrentUser(*currentUser);
    }

//##########################################################################################################

    if(username == "")
    {
        presentError(INCOMPLETE_INFORMATION_MESSAGE);
        return;
    } else
    {
        switch(type)
        {
            case Administrator:
                (*currentUser) = new AdministratorUser(firstname, lastname, username, id);
                break;
            case Student:
                (*currentUser) = new StudentUser(firstname, lastname, username, id);
                break;
        }

        /*  Query DB for user log in information   */
        if(Storage::defaultStorage().loginUserWithUsername(username, **currentUser) != 0)
        {
            //error occured
            delete *currentUser;
            *currentUser = NULL;
            presentError(LOGIN_ERROR_MESSAGE);
            return;
        }

    }


    // Add the current user to the session after successful login
    CupidSession::getInstance()->setCurrentUser(*currentUser);
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
