#ifndef PPPCONTROLLER_H
#define PPPCONTROLLER_H

#include <QObject>
#include "profilewidget.h"
#include "Models/qualification.h"
#include "Models/projectpartnerprofile.h"

enum ProfileState
{
    Viewing = 0,
    Editing,
    NoProfile
};

class PPPController : public QObject
{
    Q_OBJECT
    ProfileWidget *profileView;
    ProjectPartnerProfile *profile;

    void didSetProfile();
    void enableInteractions(bool);
    void setupUIForState(ProfileState);
    void populateProfileView();
    void updatePPP();

public:
    explicit PPPController(ProfileWidget*, QObject *parent = 0);
    ~PPPController();

signals:

public slots:
    void editPPP();
    void savePPP();
    void createPPP();

};

#endif // PPPCONTROLLER_H
