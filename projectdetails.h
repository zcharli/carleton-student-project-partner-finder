#ifndef PROJECTDETAILS_H
#define PROJECTDETAILS_H

#include <QWidget>
#include "Models/project.h"

namespace Ui {
class ProjectDetails;
}

class ProjectDetails : public QWidget
{
    Q_OBJECT

public:
    ProjectDetails(Project*, QWidget *parent = 0);
    ~ProjectDetails();

    /*!
     *  @param: none
     *   @desc: populates the current project data into the view
     * @return: void
    */
    void viewWillAppear();

signals:
    /*!
     *  @param: void
     *   @desc: A signal emitted when the registration button is clicked
     * @return: void
    */
    void registrationClicked();

    /*!
     *  @param: void
     *   @desc: A signal emitted when the start algorithm button is clicked
     * @return: void
    */
    void startAlgoClicked();

public slots:
    void on_btnRegistration_clicked();
    void on_btnStartAlgo_clicked();
    void handleUserContextSwitch();

private:
    Ui::ProjectDetails *ui;
    Project* projectViewing;
    bool isRegistered;
};

#endif // PROJECTDETAILS_H
