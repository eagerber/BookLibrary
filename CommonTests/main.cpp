#include <QtTest/QtTest>

#include "cbooktests.h"
#include "clibrarytests.h"


int main()
{
    CBookTests bookTests;
    QTest::qExec(&bookTests);

    CLibraryTests libraryTests;

    QTest::qExec(&libraryTests);
    return 0;
}
