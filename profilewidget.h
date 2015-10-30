#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>
#include "cupidslider.h"
#include "ui_profilewidget.h"
#include "Models/projectpartnerprofile.h"


namespace Ui {
class ProfileWidget;
}

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileWidget(QWidget *parent = 0);
    ~ProfileWidget();

    Ui::ProfileWidget& getUI();

    /*
     * All of the custom sliders required for User Coding and technical knowledge
     */
    CupidSlider* sliderUserOO;
    CupidSlider* sliderUserUI;
    CupidSlider* sliderUserScripting;
    CupidSlider* sliderUserDB;
    CupidSlider* sliderUserDesignPatterns;
    CupidSlider* sliderUserDataStructures;
    CupidSlider* sliderUserComputerSecurity;
    CupidSlider* sliderUserSoftwareDocumentation;
    CupidSlider* sliderUserNetworkComputing;
    CupidSlider* sliderUserVersionControl;
    CupidSlider* sliderUserWebDevelopment;

    /*
     * All of the custom sliders required for Teammate Coding and technical knowledge
     */
    CupidSlider* sliderTeammateOO;
    CupidSlider* sliderTeammateUI;
    CupidSlider* sliderTeammateScripting;
    CupidSlider* sliderTeammateDB;
    CupidSlider* sliderTeammateDesignPatterns;
    CupidSlider* sliderTeammateDataStructures;
    CupidSlider* sliderTeammateComputerSecurity;
    CupidSlider* sliderTeammateSoftwareDocumentation;
    CupidSlider* sliderTeammateNetworkComputing;
    CupidSlider* sliderTeammateVersionControl;
    CupidSlider* sliderTeammateWebDevelopment;

    int numBoxSelected;

    void enableDisableCheckBoxes();

signals:
    void userToEditPPP();
    void userToSavePPP();
    void userToCreatePPP();

private:
    void didSetProfile();

private slots:

    void on_btnSave_clicked();

    void on_btnEditPPP_clicked();

    void on_btnCreatePPP_clicked();

    void on_chkHardworking_clicked();

    void on_chkFlexible_clicked();

    void on_chkImpulsive_clicked();

    void on_chkHumour_clicked();

    void on_chkEfficient_clicked();

    void on_chkProactive_clicked();

    void on_chkOrganized_clicked();

    void on_chkDependable_clicked();

private:
    Ui::ProfileWidget *ui;
};

#endif // PROFILEWIDGET_H
