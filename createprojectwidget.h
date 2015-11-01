#ifndef CREATEPROJECTWIDGET_H
#define CREATEPROJECTWIDGET_H

#include <QWidget>
#include <QString>
#include "Models/project.h"

namespace Ui {
class CreateProjectWidget;
}

class CreateProjectWidget : public QWidget
{
    Q_OBJECT
    void presentError(QString* errorMessage);

    /*  API for functionality   */
    Project *project;

    void setUpNewProject();
    void saveNewProject();

public:
    explicit CreateProjectWidget(QWidget *parent = 0);
    ~CreateProjectWidget();

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


private slots:

    void on_btnSave_clicked();

private:
    Ui::CreateProjectWidget *ui;
};

#endif // CREATEPROJECTWIDGET_H
