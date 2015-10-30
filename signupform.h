#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>
#include "Models/user.h"

namespace Ui {
class SignUpForm;
}

class SignUpForm : public QWidget
{
    Q_OBJECT

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
     *       @param: errorStringToPresent: QString
     *        @desc: presents a string of error text to the user
     *      @return: void
     */
    void presentError(QString errorString);

public:
    explicit SignUpForm(QWidget *parent = 0);
    ~SignUpForm();

signals:
    /*!
     *  @param: clear
     *   @desc: A signal emitted when the signup is performed.
     * @return: void
    */
    void signUpAccepted(User *currentUser);

public slots:
    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          Administrator User signup
     * @return: void
    */
    void slotAdministratorUserSignup();

    /*!
     *  @param: none
     *   @desc: A slot to accept the signal emitted from an
     *          Student User signup
     * @return: void
    */
    void slotStudentUserSignup();

private:
    Ui::SignUpForm *ui;

    void attemptSignUpForUser(UserType, User **);
};

#endif // SIGNUPFORM_H
