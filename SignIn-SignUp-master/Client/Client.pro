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
    signin_dialog.cpp

HEADERS  += tcpclient.h \
    signin_dialog.h

FORMS    += tcpclient.ui \
    signin_dialog.ui
