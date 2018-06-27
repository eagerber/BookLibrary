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
    CLibrary library;
    library.add(CBook());
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
