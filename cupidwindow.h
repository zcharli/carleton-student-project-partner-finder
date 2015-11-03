#ifndef CUPIDWINDOW_H
#define CUPIDWINDOW_H

#include <QMainWindow>
#include "sidebarwidget.h"
#include "profilewidget.h"
#include "settingswidget.h"
#include "createprojectwidget.h"
#include "Models/user.h"
#include "projectlistwidget.h"
#include "Controllers/pppcontroller.h"
#include "projectdetails.h"
#include "homewidget.h"

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
    //Controllers
    PPPController *pppController;

    SideBarWidget projectSidebar;
    ProfileWidget profileWidget;
    CreateProjectWidget createProjectWidget;
    ProjectListWidget projectsWidget;
    SettingsWidget settingsWidget;
    HomeWidget homeWidget;

    //Other views to be managed by the window
    ProjectDetails projectDetailsWidget;

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

    /*!
     *  @param: none
     *   @desc: A signal emitted when the current User has selected to view a project
     *  @return: void
    */
    void userToViewProject();

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
     *          home button is clicked
     * @return: void
    */

    void generateHomePage();
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
     *          discoverProjects or myProjects button is clicked
     * @return: void
    */
    void generateProjectsPage();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          logout button is clicked
     * @return: void
    */
    void logCurrentUserOut();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          Create Project Button is clicked
     * @return: void
    */
    void generateCreateProjectPage();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted after the
     *          View Project Button is clicked
     * @return: void
    */
    void generateProjectDetailsPage();

};

#endif // CUPIDWINDOW_H
