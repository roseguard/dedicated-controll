#-------------------------------------------------
#
# Project created by QtCreator 2016-08-14T18:50:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dedicatedControl
TEMPLATE = app


SOURCES += main.cpp\
        dedicatedcontrol.cpp \
    mousemover.cpp

HEADERS  += dedicatedcontrol.h \
    mousemover.h

CONFIG += mobility
MOBILITY = 

