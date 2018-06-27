#include "testutils.h"

#include <QtTest/QtTest>

TestUtils::TestUtils()
{
}

void TestUtils::Compare(const QList<CBook> &expected, const QList<CBook> &actual)
{
    QCOMPARE(expected.length(), actual.length());
    for(int i = 0; i < expected.length(); ++i)
    {
        int index = actual.indexOf(expected[i]);
        QVERIFY(expected[i] == actual[index]);
    }
}

void TestUtils::Compare(const QList<QList<CBook>> &expected, const QList<QList<CBook>> &actual)
{
    QCOMPARE(expected.length(), actual.length());
    for(int i = 0; i < expected.length(); ++i)
    {
        int index = actual.indexOf(expected[i]);

        Compare(expected[i], actual[index]);
    }
}
