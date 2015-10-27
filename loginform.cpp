#include "loginform.h"
#include <QDebug>
#include "ui_loginform.h"

#define PROG_BAR_DEFAULT_VALUE 0

#define DEBUG_USER "Leonidas"

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
    ui->progBarLogin->setValue(PROG_BAR_DEFAULT_VALUE);
}


LoginForm::~LoginForm()
{
    delete ui;
}


void LoginForm::slotAdministratorUserLogin()
{
    QString username = ui->txtLogin->text();
    if(username.compare(QString(DEBUG_USER)) == 0)
    {
        emit loginAccepted(username);
        close();
    }
}

void LoginForm::slotStudentUserLogin()
{
    QString username = ui->txtLogin->text();
    if(username.compare(QString(DEBUG_USER)) == 0)
    {
        emit loginAccepted(username);
        close();
    }
}
