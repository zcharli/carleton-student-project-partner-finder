#ifndef CUPIDWINDOW_H
#define CUPIDWINDOW_H

#include <QMainWindow>
#include "sidebarwidget.h"
#include "profilewidget.h"
#include "settingswidget.h"
#include "Models/user.h"
#include "projectlistwidget.h"

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
    ProjectListWidget projectWidget;
    SettingsWidget settingsWidget;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();

    /*!
     *       @param: none
     *        @desc: all cleanup that needs to be done before
     *               this view leaves the screen
     *      @return: void
     */
    void viewWillDisappear();

signals:
    /*!
     *  @param: none
     *   @desc: A signal emitted when the current User has been logged out
     *  @return: void
    */
    void userLoggedOut();

public slots:
    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after a
     *          successful User login from the login diaglog
     * @return: void
    */
    void acceptUserLogin();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          profile button is clicked
     * @return: void
    */
    void generateProfilePage();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          settings button is clicked
     * @return: void
    */
    void generateSettingsPage();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          logout button is clicked
     * @return: void
    */
    void logCurrentUserOut();
};

#endif // CUPIDWINDOW_H
