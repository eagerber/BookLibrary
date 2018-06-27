#ifndef CBOOKTEST_H
#define CBOOKTEST_H

#include <QtTest/QtTest>

class CBookTests: public QObject
{
    Q_OBJECT
private slots:
    void constructor();
    void assignment();
    void equal();
    void HashSumMatch();
    void id();
    void name();
    void fullPath();
    void extension();
    void size();
    void md5();
};

#endif // CBOOKTEST_H
