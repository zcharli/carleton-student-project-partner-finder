#include "loginform.h"
#include "cupidwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm cuPIDLoginForm;
    cuPIDWindow cuPIDWindow;

    //connect login dialog with main cuPID window
    QObject::connect(&cuPIDLoginForm, SIGNAL(loginAccepted(QString&)),
                     &cuPIDWindow, SLOT(acceptUserLogin(QString&)));

    cuPIDLoginForm.show();

    return a.exec();
}
