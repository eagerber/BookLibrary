#include <QtTest/QtTest>

#include "cbook.h"

class CBookTests: public QObject
{
    Q_OBJECT
private slots:
    void constructor();
    void assignment();
    void equalById();
    void fullMatch();
    void id();
    void name();
    void fullPath();
    void extension();
    void size();
    void md5();
};

void CBookTests::constructor()
{
    CBook book1();
    CBook book2(1, "", "", "", 1, QByteArray());
    CBook book3(book2);

    QVERIFY(book2.FullMatch(book3));
}

void CBookTests::assignment()
{
    CBook book2;
    CBook book3 = book2;

    QVERIFY(book2.FullMatch(book3));
}

void CBookTests::equalById()
{
    CBook book1(1, "", "", "", 1, QByteArray());
    CBook book2(1, "a", "b", "c", 2, QByteArray());

    QVERIFY(book1 == book2);
}

void CBookTests::fullMatch()
{
    CBook book1(1, "a", "b", "c", 1, QByteArray());
    CBook book2(1, "a", "b", "c", 1, QByteArray());

    QVERIFY(book1.FullMatch(book2));
    QVERIFY(book2.FullMatch(book1));

    CBook book3(2, "a", "b", "c", 1, QByteArray());
    QVERIFY(!book2.FullMatch(book3));
    QVERIFY(!book3.FullMatch(book2));
}

void CBookTests::id()
{
    int expectedId = 100500;
    CBook book(expectedId, "a", "b", "c", 1, QByteArray());

    QCOMPARE(expectedId, book.id());
}

void CBookTests::name()
{
    QString expectedName = "ExpectedName";
    CBook book(1, expectedName, "b", "c", 1, QByteArray());

    QCOMPARE(expectedName, book.name());
}

void CBookTests::fullPath()
{
    QString expectedFullPath = "ExpectedFullPath";
    CBook book(1, "a", expectedFullPath, "c", 1, QByteArray());

    QCOMPARE(expectedFullPath, book.fullPath());
}

void CBookTests::extension()
{
    QString expectedExtension = "ExpectedExtension";
    CBook book(1, "a", "b", expectedExtension, 1, QByteArray());

    QCOMPARE(expectedExtension, book.extension());
}

void CBookTests::size()
{
    int expectedSize= 100500;
    CBook book(1, "a", "b", "c", expectedSize, QByteArray());

    QCOMPARE(expectedSize, book.size());
}

void CBookTests::md5()
{
    QByteArray expectedMd5 = QByteArray(1, 255);
    CBook book(1, "a", "b", "c", 1, expectedMd5);

    QCOMPARE(expectedMd5, book.md5());
}


QTEST_MAIN(CBookTests)
#include "cbooktests.moc"
