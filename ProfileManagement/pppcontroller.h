#ifndef PPPCONTROLLER_H
#define PPPCONTROLLER_H

#include "profilewidget.h"

//  Subsystem dependencies
#include "DataAccessLayer/qualification.h"
#include "DataAccessLayer/projectpartnerprofileproxy.h"


#include <QObject>
#include <QProcess>
#include <QTimer>

enum ProfileState
{
    Viewing = 0,
    Editing,
    NoProfile,
    CodingQuestion
};

class PPPController : public QObject
{
    Q_OBJECT
    ProfileWidget *profileView;
    ProjectPartnerProfile *profile;
    QProcess *codeMarker;
    QTimer *timer;
    bool markingSuccessful;
    bool newUserAnsweredCodingQuestion;
    ProfileState currentState;

    void didSetProfile();
    void enableInteractions(bool);
    void setupUIForState(ProfileState);
    void populateProfileView();
    void updatePPP();
    void retrievePPP();
    bool validateProfileForm();

public:
    explicit PPPController(ProfileWidget*, QObject *parent = 0);
    ~PPPController();

signals:

public slots:
    void editPPP();
    void savePPP();
    void createPPP();
    void codingTimerFinished();
    void saveScoreForCodingQuestion();
    void processFinishedMarkingQuestion();
    void handleContextSwitchToView();
    void handleContexSwitchAwayFromView();
};

#endif // PPPCONTROLLER_H
