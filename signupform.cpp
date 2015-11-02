#include "signupform.h"
#include "ui_signupform.h"
#include "Models/studentuser.h"
#include "Models/administratoruser.h"
#include "Repository/storage.h"
#include <QMessageBox>

#define INCOMPLETE_INFORMATION_ERROR "Please fill out all fields"
#define SIGN_UP_ERROR_MESSAGE "Something went wrong"

SignUpForm::SignUpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpForm)
{
    ui->setupUi(this);

    connect(ui->btnAdministrator, &QPushButton::clicked, this, &SignUpForm::slotAdministratorUserSignup);
    connect(ui->btnStudent, &QPushButton::clicked, this, &SignUpForm::slotStudentUserSignup);

    viewWillAppear();
}

SignUpForm::~SignUpForm()
{
    delete ui;
}


void SignUpForm::viewWillAppear()
{
    ui->txtFirstName->setText("");
    ui->txtLastName->setText("");
    ui->txtUsername->setText("");
}


void SignUpForm::viewWillDisappear()
{
    ui->txtFirstName->setText("");
    ui->txtLastName->setText("");
    ui->txtUsername->setText("");
}

void SignUpForm::presentError(QString errorString)
{
    //TODO:
    QMessageBox messageBox;
    messageBox.critical(0,"Error",errorString);
    messageBox.setFixedSize(500,200);
}

void SignUpForm::attemptSignUpForUser(UserType type, User **currentUser)
{
    QString fName = ui->txtFirstName->text();
    QString lName = ui->txtLastName->text();
    QString username = ui->txtUsername->text();

    if (fName == "" || lName == "" || username == "")
    {
        presentError(QString(INCOMPLETE_INFORMATION_ERROR));
        return;
    }

    switch(type)
    {
        case Administrator:
            (*currentUser) = new AdministratorUser(fName, lName, username, 0);
            break;
        case Student:
            (*currentUser) = new StudentUser(fName, lName, username, 0);
            break;
    }

    //Do database signup attempt here
    int successStatus = Storage::defaultStorage().signupUser(**currentUser);
    if(successStatus == 0)
        return;
    else
    {
        delete (*currentUser);  //Something went wrong in database.
        *currentUser = NULL;
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Either this username or something terrible happened to the database.");
        messageBox.setFixedSize(500,200);
    }
}


void SignUpForm::slotAdministratorUserSignup()
{
    /*  Create User entity here
     *  We will need to fetch the information
     *  from the data base here
     */
    User *currentUser = NULL;
    attemptSignUpForUser(Administrator, &currentUser);

    if (currentUser != NULL)
    {
        emit signUpAccepted(currentUser);
        viewWillDisappear();
        close();
    }
    else
        presentError(QString(SIGN_UP_ERROR_MESSAGE));
}


void SignUpForm::slotStudentUserSignup()
{
    /*  Create User entity here
     *  We will need to fetch the information
     *  from the data base here
     */
    User *currentUser = NULL;
    attemptSignUpForUser(Student, &currentUser);

    if (currentUser != NULL)
    {
        emit signUpAccepted(currentUser);
        viewWillDisappear();
        close();
    }
    else
        presentError(QString(SIGN_UP_ERROR_MESSAGE));
}
