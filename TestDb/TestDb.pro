#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T11:54:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestDb
TEMPLATE = app

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
    FilterLineEdit.cpp \
    FilterTableHeader.cpp \
    findduplicatesdialog.cpp

HEADERS  += mainwindow.h \
    settingswindow.h \
    FilterLineEdit.h \
    FilterTableHeader.h \
    findduplicatesdialog.h

FORMS    += mainwindow.ui \
    settingswindow.ui \
    findduplicatesdialog.ui
