#include "loginform.h"
#include <QDebug>
#include "ui_loginform.h"
#include "Models/administratoruser.h"
#include "Models/studentuser.h"
#include "Models/cupidsession.h"

#define PROG_BAR_DEFAULT_VALUE 0

#define DEBUG_USER "Leonidas"

/*  Generic Error Messages For the login Screen     */
#define INVALID_USERNAME_MESSAGE "Validation for specified Username failed. Please try again."

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(ui->btnAdministrator, &QPushButton::clicked, this, &LoginForm::slotAdministratorUserLogin);
    connect(ui->btnStudent, &QPushButton::clicked, this, &LoginForm::slotStudentUserLogin);

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

    if(username.compare(QString(DEBUG_USER)) == 0)
    {
        // create debug firstname, lastname and id
        firstname = "Jack";
        lastname = "Brown";
        id = 7;
    }
    else
    {
        return;
    }
    switch(type)
    {
        case Administrator:
            (*currentUser) = new AdministratorUser(firstname, lastname, username, id);
            break;
        case Student:
            (*currentUser) = new StudentUser(firstname, lastname, username, id);
            break;
    }

    // Add the current user to the session
    CupidSession::getInstance()->setCurrentUser(*currentUser);
}

void LoginForm::presentError(QString errorString)
{
    ui->eLabel->setText(errorString);
    ui->eLabel->show();
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


void LoginForm::promptUserLogin()
{
    viewWillAppear();
    show();
}
