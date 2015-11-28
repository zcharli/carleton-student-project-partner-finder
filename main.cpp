#include "cupidwindow.h"
#include <QFile>
// Subsystem dependencies
#include "UserAuthentication/loginform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("../cupid/Stylesheets/style.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    LoginForm cuPIDLoginForm;
    cuPIDWindow cuPIDWindow;

    //connect login dialog with main cuPID window
    QObject::connect(&cuPIDLoginForm, SIGNAL(loginAccepted()),
                     &cuPIDWindow, SLOT(acceptUserLogin()));
    QObject::connect(&cuPIDWindow, SIGNAL(userLoggedOut()),
                     &cuPIDLoginForm, SLOT(promptUserLogin()));

    cuPIDLoginForm.show();

    return a.exec();
}
