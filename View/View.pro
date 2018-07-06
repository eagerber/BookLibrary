#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T15:04:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = View
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../DatabaseAdapter
INCLUDEPATH += ../Common
INCLUDEPATH += ../Utils

debug
{
    DESTDIR = ../debug
    OBJECTS_DIR = ../debug/.obj
    MOC_DIR = ../debug/.moc
    RCC_DIR = ../debug/.rcc
    UI_DIR = ../debug/.ui

    LIBS += -L../debug/ -lDatabaseAdapter
    LIBS += -L../debug/ -lCommon
    LIBS += -L../debug/ -lUtils
}

release
{
    DESTDIR = ../release
    OBJECTS_DIR = ../release/.obj
    MOC_DIR = ../release/.moc
    RCC_DIR = ../release/.rcc
    UI_DIR = ../release/.ui

    LIBS += -L../release/ -lDatabaseAdapter
    LIBS += -L../release/ -lCommon
    LIBS += -L../release/ -lUtils
}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    automaticduplicatesprocessdialog.cpp \
    findduplicatesdialog.cpp \
    settingswindow.cpp

HEADERS += \
        mainwindow.h \
    automaticduplicatesprocessdialog.h \
    findduplicatesdialog.h \
    settingswindow.h

FORMS += \
        mainwindow.ui \
    automaticduplicatesprocessdialog.ui \
    findduplicatesdialog.ui \
    settingswindow.ui
