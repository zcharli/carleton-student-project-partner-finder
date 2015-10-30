#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include "ui_sidebarwidget.h"  //Side effect of creating a getter to the ui element of the class, but this makes things easier

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SideBarWidget(QWidget *parent = 0);
    ~SideBarWidget();

    /*!
     *  @param: none
     *   @desc: returns the ui elements of the sideBarWidget
     * @return: ui: Ui::SideBarWidget*
    */
    Ui::SideBarWidget* getUI();

signals:
    /*!
     *  @param: void
     *   @desc: A signal emitted when the profile button is clicked
     * @return: void
    */
    void profileClicked();

    /*!
     *  @param: void
     *   @desc: A signal emitted when the logout button is clicked
     * @return: void
    */
    void logOutClicked();

    /*!
     *  @param: void
     *   @desc: A signal emitted when the settings button is clicked
     * @return: void
    */
    void settingsClicked();

    /*!
     *  @param: void
     *   @desc: A signal emitted when the dicoverProjects button is clicked
     * @return: void
    */
    void discoverProjectsClicked();

public slots:
    void on_btnProfile_clicked();
    void on_btnLogOut_clicked();
    void on_btnSettings_clicked();
    void on_btnDiscoverProjects_clicked();

private:
    Ui::SideBarWidget *ui;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();
};

#endif // SIDEBARWIDGET_H
