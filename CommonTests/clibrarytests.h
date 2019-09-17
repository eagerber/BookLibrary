#ifndef CLIBRARYTESTS_H
#define CLIBRARYTESTS_H

#include <QtTest/QtTest>

#include "clibrary.h"

class CLibraryTests: public QObject
{
    Q_OBJECT
private slots:
    void constructor();
    void add();
    void doppelgangers();
    void allDoppelgangers();
    void count();
private:
    CLibrary filledLibrarywithPrefix(QString prefix, int count);
};


#endif // CLIBRARYTESTS_H
