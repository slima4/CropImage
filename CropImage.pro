#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T22:16:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CropImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boxitem.cpp \
    graphicsview.cpp

HEADERS  += mainwindow.h \
    boxitem.h \
    graphicsview.h

FORMS    += mainwindow.ui
