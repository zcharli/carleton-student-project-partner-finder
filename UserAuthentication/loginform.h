#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "signupform.h"

//  Subsystem dependencies
#include "DataAccessLayer/user.h"

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
     *  @param: clear
     *   @desc: A signal emitted when the login is performed.
     *          username the username entered in the dialog
     * @return: void
    */
    void loginAccepted();

private:
    Ui::LoginForm *ui;

    SignUpForm signUpForm;

    /*!
     *       @param: none
     *        @desc: all setup that needs to be done
     *               before this object appears on screen to the user.
     *      @return: void
     */
    void viewWillAppear();

    /*!
     *       @param: none
     *        @desc: all clean up that needs to be done before
     *               this view dissapears from the screen
     *      @return: void
     */
    void viewWillDisappear();

    /*!
     *  @param: usernameToValidate: QString&
     *  @desc: gets the currentUser with the given username
     *  @return: currentUser: User* (null if validation failed)
     */
    void getCurrentUserWithUserName(QString& username, UserType type, User **currentUser);

    /*!
     *       @param: errorStringToPresent: QString
     *        @desc: presents a string of error text to the user
     *      @return: void
     */
    void presentError(QString errorString);

    /*!
     *       @param: userToPopulate: User*
     *        @desc: populate the user with the id of the projects he is registered in
     *      @return: void
     */
    void populateUserProjects(User *);

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

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from a successful signup
     * @return: void
    */
    void signUpSucceeded(User *);

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          successful user logout
     * @return: void
    */
    void promptUserLogin();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          attempt to create a new account
     * @return: void
    */
    void slotCreateNewAccount();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          attempt to go back to login from a sign up
     * @return: void
    */
    void slotBackToLoginpage();
};

#endif // LOGINFORM_H
