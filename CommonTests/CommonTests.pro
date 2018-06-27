#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T11:11:09
#
#-------------------------------------------------

QT += core testlib
QT       -= gui

TARGET = CommonTests
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

DEFINES += COMMONTESTS_LIBRARY

INCLUDEPATH += ../Common
INCLUDEPATH += ../TestUtils

debug
{
    DESTDIR = ../debug/tests
    OBJECTS_DIR = ../debug/tests/.obj
    MOC_DIR = ../debug/tests/.moc
    RCC_DIR = ../debug/tests/.rcc
    UI_DIR = ../debug/tests/.ui

    LIBS += -L../debug/ -lCommon
    LIBS += -L../debug/ -lTestUtils
}

release
{
    DESTDIR = ../release/tests
    OBJECTS_DIR = ../release/tests/.obj
    MOC_DIR = ../release/tests/.moc
    RCC_DIR = ../release/tests/.rcc
    UI_DIR = ../release/tests/.ui

    LIBS += -L../release/ -lCommon
    LIBS += -L../release/ -lTestUtils
}


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cbooktests.cpp \
    clibrarytests.cpp \
    main.cpp

HEADERS += \
    clibrarytests.h \
    cbooktests.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
