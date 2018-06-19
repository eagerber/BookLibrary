#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T11:54:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestDb
TEMPLATE = app

Release:DESTDIR = ../release
Release:OBJECTS_DIR = ../release/.obj
Release:MOC_DIR = ../release/.moc
Release:RCC_DIR = ../release/.rcc
Release:UI_DIR = ../release/.ui

Debug:DESTDIR = ../debug
Debug:OBJECTS_DIR = ../debug/.obj
Debug:MOC_DIR = ../debug/.moc
Debug:RCC_DIR = ../debug/.rcc
Debug:UI_DIR = ../debug/.ui

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    settingswindow.cpp \
    findduplicatesdialog.cpp \
    automaticduplicatesprocessdialog.cpp \
    cdopelgangerslibrary.cpp \
    cbook.cpp \
    cbooklist.cpp

HEADERS  += mainwindow.h \
    settingswindow.h \
    findduplicatesdialog.h \
    automaticduplicatesprocessdialog.h \
    cdopelgangerslibrary.h \
    cbook.h \
    cbooklist.h

FORMS    += mainwindow.ui \
    settingswindow.ui \
    findduplicatesdialog.ui \
    automaticduplicatesprocessdialog.ui
