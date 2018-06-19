QT += core sql
QT -= gui

CONFIG += c++11

TARGET = DataProvider
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = lib

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

SOURCES += main.cpp \
    cbook.cpp \
    cdatabase.cpp \
    cdatabaseadapter.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    cbook.h \
    cdatabase.h \
    cdatabaseadapter.h
