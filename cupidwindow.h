#ifndef CUPIDWINDOW_H
#define CUPIDWINDOW_H

#include <QMainWindow>
#include "sidebarwidget.h"
#include "profilewidget.h"
#include "Models/user.h"

namespace Ui {
class cuPIDWindow;
}

class cuPIDWindow : public QMainWindow
{
    Q_OBJECT


public:
        Ui::cuPIDWindow *ui;
    explicit cuPIDWindow(QWidget *parent = 0);
    ~cuPIDWindow();
    void displayProfile(ProfileWidget*);
private:

    SideBarWidget projectSidebar;
    ProfileWidget profileWidget;
    /*
     * reference current user of the cuPID system
     */
    User *currentUser;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();

public slots:
    /*!
     *  @param: user: User* (input);
     *   @desc: A slot to accept the signal emitted after a
     *          successful User login from the login diaglog
     * @return: void
    */
    void acceptUserLogin(User* user);
    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          profile button is clicked
     * @return: void
    */
    void generateProfilePage();
};

#endif // CUPIDWINDOW_H
