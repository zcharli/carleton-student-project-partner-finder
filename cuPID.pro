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
    Repository/dataaccessdispatcher.cpp \
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
    ProjectManagement/projectdetailsview.cpp \
    ProjectManagement/createprojectwidget.cpp \
    ProjectManagement/editteamconfigurationsdialog.cpp \
    ProjectManagement/projectcellwidget.cpp \
    ProjectManagement/projectlistview.cpp \
    ProfileManagement/profilewidget.cpp \
    ProfileManagement/cupidslider.cpp \
    ProfileManagement/pppcontroller.cpp \
    ProfileManagement/codingwidget.cpp \
    ProjectManagement/projectlistmanagerfactory.cpp \
    ProjectManagement/abstractprojectmanagerfactory.cpp \
    ProjectManagement/projectdetailsmanagerfactory.cpp \
    ProjectManagement/createprojectmanagerfactory.cpp \
    ProjectManagement/abstractprojectcontroller.cpp \
    ProjectManagement/projectlistcontroller.cpp \
    ProjectManagement/projectdetailscontroller.cpp \
    ProjectManagement/createprojectcontroller.cpp \
    ProjectManagement/abstractprojectview.cpp \
    AlgorithmExecution/insomniamatchingalgorithm.cpp \
    AlgorithmExecution/team.cpp \
    main.cpp \
    sidebarwidget.cpp \
    settingswidget.cpp \
    cupidwindow.cpp \
    homewidget.cpp \
    highlighter.cpp \
    AlgorithmExecution/matchreportview.cpp


HEADERS  += \
    Repository/projectrepository.h \
    Repository/userrepository.h \
    Repository/databasemanager.h \
    Repository/dataaccessdispatcher.h \
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
    DataAccessLayer/mapconfigs.h \
    UserAuthentication/signupform.h \
    UserAuthentication/loginform.h \
    ProjectManagement/createprojectwidget.h \
    ProjectManagement/editteamconfigurationsdialog.h \
    ProjectManagement/projectcellwidget.h \
    ProjectManagement/projectlistview.h \
    ProjectManagement/projectdetailsview.h \
    ProfileManagement/profilewidget.h \
    ProfileManagement/cupidslider.h \
    ProfileManagement/pppcontroller.h \
    ProfileManagement/codingwidget.h \
    ProjectManagement/projectlistmanagerfactory.h \
    ProjectManagement/abstractprojectmanagerfactory.h \
    ProjectManagement/projectdetailsmanagerfactory.h \
    ProjectManagement/createprojectmanagerfactory.h \
    ProjectManagement/abstractprojectcontroller.h \
    ProjectManagement/projectlistcontroller.h \
    ProjectManagement/projectdetailscontroller.h \
    ProjectManagement/createprojectcontroller.h \
    ProjectManagement/abstractprojectview.h \
    AlgorithmExecution/insomniamatchingalgorithm.h \
    AlgorithmExecution/team.h \
    errorcodes.h \
    sidebarwidget.h \
    settingswidget.h \
    cupidwindow.h \
    homewidget.h \
    highlighter.h \
    AlgorithmExecution/matchreportview.h

FORMS    += \
    UserAuthentication/loginform.ui \
    UserAuthentication/signupform.ui \
    ProjectManagement/createprojectwidget.ui \
    ProjectManagement/editteamconfigurationsdialog.ui \
    ProjectManagement/projectcellwidget.ui \
    ProfileManagement/profilewidget.ui \
    ProjectManagement/projectdetailsview.ui \
    cupidwindow.ui \
    settingswidget.ui \
    sidebarwidget.ui \
    homewidget.ui \
    ProfileManagement/codingwidget.ui \
    AlgorithmExecution/matchreportview.ui

RESOURCES += \
    stylesheet.qrc

OTHER_FILES +=
