#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T19:01:47
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fapman
TEMPLATE = app
SUBDIRS += \
    images

SOURCES += main.cpp\
        mainwindow.cpp \
       cpuristin.cpp \
    rotatedialog.cpp

HEADERS  += mainwindow.h \
          cpuristin.h \
    rotatedialog.h

FORMS    += mainwindow.ui \
    rotatedialog.ui

RESOURCES += \
    resources.qrc
