#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T18:01:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        tcpclient.cpp \
    signin_dialog.cpp \
    findpsddialog.cpp \
    talantoo.cpp \
    sendfiledialog.cpp \
    reveivedialog.cpp

HEADERS  += tcpclient.h \
    signin_dialog.h \
    findpsddialog.h \
    talantoo.h \
    sendfiledialog.h \
    reveivedialog.h

FORMS    += tcpclient.ui \
    signin_dialog.ui \
    findpsddialog.ui \
    talantoo.ui \
    sendfiledialog.ui \
    reveivedialog.ui
