#ifndef CUPIDWINDOW_H
#define CUPIDWINDOW_H

#include <QMainWindow>

namespace Ui {
class cuPIDWindow;
}

class cuPIDWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cuPIDWindow(QWidget *parent = 0);
    ~cuPIDWindow();

private:
    Ui::cuPIDWindow *ui;

    /*
     * reference current user of the cuPID system
     */
    QString *currentUser;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();

public slots:
    /*!
     *  @param: user: QString (input);
     *   @desc: A slot to accept the signal emitted after a
     *          successful User login from the login diaglog
     * @return: void
    */
    void acceptUserLogin(QString& user);
};

#endif // CUPIDWINDOW_H
