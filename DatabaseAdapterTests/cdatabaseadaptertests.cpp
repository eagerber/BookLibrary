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
    void update();
    void saveChanges();

private:
    QList<CBook> fillWithPrefix(QString prefix, int itemsCount);
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
    QList<CBook> expectedBooks = fillWithPrefix("", 5);

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
    QList<CBook> expectedBooks = fillWithPrefix("Inserted", 15);

    QString filename = Utils::UniqueDatabaseName();
    auto *databaseAdapter = new CDatabaseAdapter(filename);

    for(int i = 0; i < expectedBooks.length(); ++i)
    {
        databaseAdapter->insert(expectedBooks[i]);
    }

    QList<CBook> actualBooks = databaseAdapter->readAll();
    TestUtils::Compare(expectedBooks, actualBooks);

    delete databaseAdapter;
    QFile::remove(filename);

}

void CDatabaseAdapterTests::update()
{
    QList<CBook> expectedBooks = fillWithPrefix("Updated", 5);

    QString filename = Utils::UniqueDatabaseName();
    QFile::copy(":/files/TestDatabase.sqlite", filename);
    QFile::setPermissions(filename, QFile::ReadOwner | QFile::WriteOwner);

    auto *databaseAdapter = new CDatabaseAdapter(filename);

    foreach (const auto& item, expectedBooks)
    {
        databaseAdapter->update(item);
    }

    QList<CBook> actualBooks = databaseAdapter->readAll();

    TestUtils::Compare(expectedBooks, actualBooks);

    delete databaseAdapter;

    QFile::remove(filename);
}

void CDatabaseAdapterTests::saveChanges()
{
    QList<CBook> expectedBooks = fillWithPrefix("NewValues", 500);

    QString filename = Utils::UniqueDatabaseName();
    QFile::copy(":/files/TestDatabase.sqlite", filename);
    QFile::setPermissions(filename, QFile::ReadOwner | QFile::WriteOwner);

    auto *databaseAdapter = new CDatabaseAdapter(filename);

    databaseAdapter->saveChanges(expectedBooks);

    QList<CBook> actualBooks = databaseAdapter->readAll();

    TestUtils::Compare(expectedBooks, actualBooks);

    delete databaseAdapter;

    QFile::remove(filename);
}

QList<CBook> CDatabaseAdapterTests::fillWithPrefix(QString prefix, int itemsCount)
{
    QList<CBook> books;
    for(int i = 0; i < itemsCount; ++i)
    {
        books.push_back(
            CBook(
                i,
                prefix + QString("Name %1").arg(i),
                prefix + QString("FullPath %1").arg(i),
                prefix + QString("Ext %1").arg(i),
                i * i,
                QByteArray().fill(i, 256)));
    }
    return books;
}


QTEST_MAIN(CDatabaseAdapterTests)
#include "cdatabaseadaptertests.moc"
