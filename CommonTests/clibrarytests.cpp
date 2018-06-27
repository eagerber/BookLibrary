#include <QtTest/QtTest>

#include "clibrary.h"

class CLibraryTests: public QObject
{
    Q_OBJECT
private slots:
    void constructor();
    void add();
};

void CLibraryTests::constructor()
{
    CLibrary library();
}

void CLibraryTests::add()
{
    CLibrary library();
    library.add(CBook());
}


QTEST_MAIN(CLibraryTests)
#include "clibrarytests.moc"
