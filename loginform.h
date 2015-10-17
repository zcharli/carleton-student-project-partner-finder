#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

signals:
    /*!
     *  @param: username: QString (output)
     *   @desc: A signal emitted when the login is performed.
     *          username the username entered in the dialog
     * @return: void
    */
    void loginAccepted(QString& username);

private:
    Ui::LoginForm *ui;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();

public slots:
    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          Administrator User login
     * @return: void
    */
    void slotAdministratorUserLogin();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          Student User login
     * @return: void
    */
    void slotStudentUserLogin();
};

#endif // LOGINFORM_H
