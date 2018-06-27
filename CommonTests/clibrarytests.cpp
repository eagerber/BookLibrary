#include "clibrarytests.h"

#include "testutils.h"


void CLibraryTests::constructor()
{
    CLibrary library();
}

void CLibraryTests::add()
{
    CLibrary library;

    library.add(CBook());
}

void CLibraryTests::doppelgangers()
{
    QByteArray hash = QUuid::createUuid().toByteArray();
    QList<CBook> expectedDoppelgangers;
    expectedDoppelgangers.push_back(CBook(1, "a1", "b1", "c1", 1, hash));
    expectedDoppelgangers.push_back(CBook(2, "a2", "b2", "c2", 2, hash));
    expectedDoppelgangers.push_back(CBook(3, "a3", "b3", "c3", 3, hash));

    CLibrary library = filledLibrarywithPrefix("Some", 100);

    foreach (const auto& item, expectedDoppelgangers)
    {
        library.add(item);
    }

    foreach (const auto& item, expectedDoppelgangers)
    {
        auto actualDoppelgangers = library.doppelgangers(item);

        TestUtils::Compare(expectedDoppelgangers, actualDoppelgangers);
    }
}

void CLibraryTests::allDoppelgangers()
{
    QList<QByteArray> hash;
    QList<QList<CBook>> expectedDoppelgangers;

    for(int i = 0; i < 2; ++i)
    {
        hash.push_back(QUuid::createUuid().toByteArray());

        QList<CBook> currentDoppelgangers;
        currentDoppelgangers.push_back(CBook(1, "a1", "b1", "c1", 1, hash[i]));
        currentDoppelgangers.push_back(CBook(2, "a2", "b2", "c2", 2, hash[i]));
        currentDoppelgangers.push_back(CBook(3, "a3", "b3", "c3", 3, hash[i]));

        expectedDoppelgangers.push_back(currentDoppelgangers);
    }

    CLibrary library = filledLibrarywithPrefix("Some", 500);

    foreach (const auto& list, expectedDoppelgangers)
    {
        foreach (const auto& item, list)
        {
            library.add(item);
        }
    }

    QList<QList<CBook>> actualDoppelgangers = library.allDoppelgangers();

    TestUtils::Compare(expectedDoppelgangers, actualDoppelgangers);
}

CLibrary CLibraryTests::filledLibrarywithPrefix(QString prefix, int count)
{
    CLibrary result;

    for(int i = 0; i < count; ++i)
    {
        result.add(CBook(
           i,
           prefix + "Name",
           prefix + "FullPath",
           prefix + "Extension",
           i * i,
           QByteArray(i, 255)));
    }

    return result;
}
