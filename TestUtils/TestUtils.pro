#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T09:44:40
#
#-------------------------------------------------

QT       -= gui
QT += core testlib

TARGET = TestUtils
TEMPLATE = lib

DEFINES += TESTUTILS_LIBRARY

INCLUDEPATH += ../Common

debug
{
    DESTDIR = ../debug
    OBJECTS_DIR = ../debug/.obj
    MOC_DIR = ../debug/.moc
    RCC_DIR = ../debug/.rcc
    UI_DIR = ../debug/.ui

    LIBS += -L../debug/ -lCommon
}

release
{
    DESTDIR = ../release
    OBJECTS_DIR = ../release/.obj
    MOC_DIR = ../release/.moc
    RCC_DIR = ../release/.rcc
    UI_DIR = ../release/.ui

    LIBS += -L../release/ -lCommon
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
        testutils.cpp

HEADERS += \
        testutils.h \
        testutils_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
