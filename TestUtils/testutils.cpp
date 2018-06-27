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
        QCOMPARE(expected[i].id(), actual[i].id());
        QCOMPARE(expected[i].fullPath(), actual[i].fullPath());
        QCOMPARE(expected[i].name(), actual[i].name());
        QCOMPARE(expected[i].extension(), actual[i].extension());
        QCOMPARE(expected[i].size(), actual[i].size());
        QCOMPARE(expected[i].md5(), actual[i].md5());
    }
}
