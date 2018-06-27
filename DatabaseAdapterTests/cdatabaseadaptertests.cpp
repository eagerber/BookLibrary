#include <QCoreApplication>

#include <QtTest/QtTest>
#include <QFile>

#include "cbook.h"
#include "cdatabaseadapter.h"
#include "utils.h"
#include "testutils.h"

class CDatabaseAdapterTests: public QObject
{
    Q_OBJECT
private slots:
    void create();
    void readAll();
    void insert();
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

    TestUtils::Compare(expectedBooks, actualBooks);

    delete databaseAdapter;

    QFile::remove(filename);
}

void CDatabaseAdapterTests::insert()
{
    QList<CBook> expectedBooks;
    int expectedBooksCount = 5;
    for(int i = 0; i < expectedBooksCount; ++i)
    {
        expectedBooks.push_back(
            CBook(
                i,
                QString("InsertedName %1").arg(i),
                QString("InsertedFullPath %1").arg(i),
                QString("InsertedExt %1").arg(i),
                i * i,
                QByteArray().fill(i, 256)));
    }

    QString filename = Utils::UniqueDatabaseName();
    auto *databaseAdapter = new CDatabaseAdapter(filename);

    for(int i = 0; i < expectedBooksCount; ++i)
    {
        databaseAdapter->insert(expectedBooks[i]);
    }

    QList<CBook> actualBooks = databaseAdapter->readAll();
    TestUtils::Compare(expectedBooks, actualBooks);

    delete databaseAdapter;
    QFile::remove(filename);

}

QTEST_MAIN(CDatabaseAdapterTests)
#include "cdatabaseadaptertests.moc"
