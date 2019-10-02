#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T10:23:39
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = Common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

INCLUDEPATH += ../Utils

debug
{
    DESTDIR = ../debug
    OBJECTS_DIR = ../debug/.obj
    MOC_DIR = ../debug/.moc
    RCC_DIR = ../debug/.rcc
    UI_DIR = ../debug/.ui

    LIBS += -L../debug/ -lUtils
}

release
{
    DESTDIR = ../release
    OBJECTS_DIR = ../release/.obj
    MOC_DIR = ../release/.moc
    RCC_DIR = ../release/.rcc
    UI_DIR = ../release/.ui

    LIBS += -L../release/ -lUtils
}

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    cbook.cpp \
    clibrary.cpp

HEADERS += \
        common_global.h \ 
    cbook.h \
    clibrary.h
