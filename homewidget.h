#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

namespace Ui {
class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = 0);
    ~HomeWidget();
    void setAdmin();
    void setStudent();

private slots:
    void on_btnCreateProject_clicked();

    void on_btnDiscoverProjects_clicked();

    void on_btnManageProjectPartnerProfile_clicked();

    void on_btnEditSettings_clicked();

signals:
    /*!
     *  @param: none
     *   @desc: A signal emitted when the create project button is clicked
     * @return: none
    */
    void createProjectClicked();

    /*!
     *  @param: none
     *   @desc: A signal emitted when the manage project partner profile button is clicked
     * @return: none
    */
    void managePPPClicked();

    /*!
     *  @param: none
     *   @desc: A signal emitted when the edit settings button is clicked
     * @return: none
    */
    void editSettingsClicked();

    /*!
     *  @param: none
     *   @desc: A signal emitted when the discover projects button is clicked
     * @return: none
    */
    void discoverProjectsClicked();


private:
    Ui::HomeWidget *ui;
};

#endif // HOMEWIDGET_H
