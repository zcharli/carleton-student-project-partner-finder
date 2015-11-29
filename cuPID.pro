#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T13:40:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuPID
TEMPLATE = app


SOURCES += \
    Repository/projectrepository.cpp \
    Repository/userrepository.cpp \
    Repository/databasemanager.cpp \
    DataAccessLayer/user.cpp \
    DataAccessLayer/studentuser.cpp \
    DataAccessLayer/administratoruser.cpp \
    DataAccessLayer/projectpartnerprofile.cpp \
    DataAccessLayer/qualification.cpp \
    DataAccessLayer/project.cpp \
    DataAccessLayer/configuration.cpp \
    DataAccessLayer/dataaccessfacade.cpp \
    DataAccessLayer/projectpartnerprofilereal.cpp \
    DataAccessLayer/projectpartnerprofileproxy.cpp \
    UserAuthentication/loginform.cpp \
    UserAuthentication/signupform.cpp \
    ProjectManagement/projectdetails.cpp \
    ProjectManagement/createprojectwidget.cpp \
    ProjectManagement/editteamconfigurationsdialog.cpp \
    ProjectManagement/projectcellwidget.cpp \
    ProjectManagement/projectlistwidget.cpp \
    ProfileManagement/profilewidget.cpp \
    ProfileManagement/cupidslider.cpp \
    ProfileManagement/pppcontroller.cpp \
    main.cpp \
    sidebarwidget.cpp \
    settingswidget.cpp \
    cupidwindow.cpp \
    homewidget.cpp \
    Repository/dataaccessdispatcher.cpp \
    AlgorithmExecution/insomniamatchingalgorithm.cpp \
    AlgorithmExecution/matchreportview.cpp \
    AlgorithmExecution/team.cpp \
    ProfileManagement/codingwidget.cpp \
    highlighter.cpp


HEADERS  += \
    Repository/projectrepository.h \
    Repository/userrepository.h \
    Repository/databasemanager.h \
    DataAccessLayer/user.h \
    DataAccessLayer/studentuser.h \
    DataAccessLayer/administratoruser.h \
    DataAccessLayer/projectpartnerprofile.h \
    DataAccessLayer/dataaccessfacade.h \
    DataAccessLayer/projectpartnerprofilereal.h \
    DataAccessLayer/projectpartnerprofileproxy.h \
    DataAccessLayer/qualification.h \
    DataAccessLayer/project.h \
    DataAccessLayer/configuration.h \
    DataAccessLayer/imappable.h \
    UserAuthentication/signupform.h \
    UserAuthentication/loginform.h \
    ProjectManagement/createprojectwidget.h \
    ProjectManagement/editteamconfigurationsdialog.h \
    ProjectManagement/projectcellwidget.h \
    ProjectManagement/projectlistwidget.h \
    ProjectManagement/projectdetails.h \
    ProfileManagement/profilewidget.h \
    ProfileManagement/cupidslider.h \
    ProfileManagement/pppcontroller.h \
    errorcodes.h \
    sidebarwidget.h \
    settingswidget.h \
    cupidwindow.h \
    homewidget.h \
    Repository/dataaccessdispatcher.h \
    AlgorithmExecution/insomniamatchingalgorithm.h \
    AlgorithmExecution/matchreportview.h \
    AlgorithmExecution/team.h \
    ProfileManagement/codingwidget.h \
    highlighter.h

FORMS    += \
    UserAuthentication/loginform.ui \
    UserAuthentication/signupform.ui \
    ProjectManagement/createprojectwidget.ui \
    ProjectManagement/editteamconfigurationsdialog.ui \
    ProjectManagement/projectcellwidget.ui \
    ProfileManagement/profilewidget.ui \
    ProjectManagement/projectdetails.ui \
    cupidwindow.ui \
    settingswidget.ui \
    sidebarwidget.ui \
    homewidget.ui \
    ProfileManagement/codingwidget.ui

RESOURCES += \
    stylesheet.qrc

OTHER_FILES +=
