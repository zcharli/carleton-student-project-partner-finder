#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T13:40:43
#
#-------------------------------------------------

QT       += core gui

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
    projectlistwidget.cpp

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
    projectlistwidget.h


FORMS    += \
    cupidwindow.ui \
    loginform.ui \
    sidebarwidget.ui \
    profilewidget.ui
