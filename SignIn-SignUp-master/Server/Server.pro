#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T15:08:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
    tcpserver.cpp

HEADERS  += \
    tcpserver.h

FORMS    += \
    tcpserver.ui

CONFIG += console
