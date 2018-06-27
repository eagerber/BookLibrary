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
        QVERIFY(actual.indexOf(expected[i]) > -1);
    }
}
