#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T20:41:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetris1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp \
    figura.cpp

HEADERS  += mainwindow.h \
    map.h \
    figura.h

FORMS    += mainwindow.ui
