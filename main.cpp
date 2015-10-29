#include "loginform.h"
#include "cupidwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
