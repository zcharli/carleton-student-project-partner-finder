#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SideBarWidget(QWidget *parent = 0);
    ~SideBarWidget();
    void setUsername(const QString strUsername);

signals:
    /*!
     *  @param: username: QString (output)
     *   @desc: A signal emitted when the login is performed.
     *          username the username entered in the dialog
     * @return: void
    */
    void profileClicked();

public slots:
    void on_btnProfile_clicked();

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
