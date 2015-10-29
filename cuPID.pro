#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T13:40:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuPID
TEMPLATE = app


SOURCES += main.cpp\
    cupidwindow.cpp \
    loginform.cpp \
    sidebarwidget.cpp \
    profilewidget.cpp \
    cupidslider.cpp \
    Models/user.cpp \
    Models/studentuser.cpp \
    Models/administratoruser.cpp \
    Models/projectpartnerprofile.cpp \
    Models/qualification.cpp \
    Models/project.cpp \
    Models/configuration.cpp \
    settingswidget.cpp \
    Repository/projectrepository.cpp \
    Repository/userrepository.cpp \
    Repository/databasemanager.cpp

HEADERS  += \
    cupidwindow.h \
    loginform.h \
    sidebarwidget.h \
    profilewidget.h \
    cupidslider.h \
    Models/user.h \
    Models/studentuser.h \
    Models/administratoruser.h \
    Models/projectpartnerprofile.h \
    Models/qualification.h \
    Models/project.h \
    Models/configuration.h \
    settingswidget.h \
    Repository/irepository.h \
    Repository/projectrepository.h \
    Repository/userrepository.h \
    Repository/databasemanager.h


FORMS    += \
    cupidwindow.ui \
    loginform.ui \
    sidebarwidget.ui \
    profilewidget.ui \
    settingswidget.ui

RESOURCES += \
    Resources.qrc

copydata.commands = $(COPY_DIR) $$PWD/Data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
