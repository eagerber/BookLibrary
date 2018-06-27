#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "testutils_global.h"

#include <QList>
#include "cbook.h"

class TESTUTILSSHARED_EXPORT TestUtils
{

public:
    TestUtils();

    static void Compare(const QList<CBook> &expected, const QList<CBook> &actual);
    static void Compare(const QList<QList<CBook>> &expected, const QList<QList<CBook>> &actual);
};

#endif // TESTUTILS_H
