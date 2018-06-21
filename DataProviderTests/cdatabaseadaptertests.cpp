#include <QCoreApplication>

#include <QtTest/QtTest>
#include <QFile>

#include "cbook.h"
#include "cdatabaseadapter.h"
#include "utils.h"

class CDatabaseAdapterTests: public QObject
{
    Q_OBJECT
private slots:
    void create();
    void readAll();
};

void CDatabaseAdapterTests::create()
{
    QString filename = Utils::UniqueDatabaseName();
    auto *databaseAdapter = new CDatabaseAdapter(filename);

    delete databaseAdapter;

    QFile::remove(filename);
}

void CDatabaseAdapterTests::readAll()
{
    QList<CBook> expectedBooks;
    int expectedBooksCount = 5;
    for(int i = 0; i < expectedBooksCount; ++i)
    {
        expectedBooks.push_back(
            CBook(
                i,
                QString("Name %1").arg(i),
                QString("FullPath %1").arg(i),
                QString("Ext %1").arg(i),
                i * i,
                QByteArray().fill(i, 256)));
    }


    QString filename = Utils::UniqueDatabaseName();
    QFile::copy(":/files/TestDatabase.sqlite", filename);
    QFile::setPermissions(filename, QFile::ReadOwner | QFile::WriteOwner);

    auto *databaseAdapter = new CDatabaseAdapter(filename);

    QList<CBook> actualBooks = databaseAdapter->readAll();

    QCOMPARE(expectedBooks.length(), actualBooks.length());
    for(int i = 0; i < expectedBooksCount; ++i)
    {
        QCOMPARE(expectedBooks[i].id(), actualBooks[i].id());
        QCOMPARE(expectedBooks[i].fullPath(), actualBooks[i].fullPath());
        QCOMPARE(expectedBooks[i].name(), actualBooks[i].name());
        QCOMPARE(expectedBooks[i].extension(), actualBooks[i].extension());
        QCOMPARE(expectedBooks[i].size(), actualBooks[i].size());
        QCOMPARE(expectedBooks[i].md5(), actualBooks[i].md5());
    }

    delete databaseAdapter;

    QFile::remove(filename);
}

QTEST_MAIN(CDatabaseAdapterTests)
#include "cdatabaseadaptertests.moc"
