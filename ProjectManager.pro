#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T10:33:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManager
TEMPLATE = app

TRANSLATIONS = PM_zh_CN.ts \
    PM_en.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    titleBar.cpp

HEADERS  += mainwindow.h \
    titleBar.h

FORMS    += mainwindow.ui

RESOURCES += \
    PM.qrc

