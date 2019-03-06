#include "cdatabaseadapter.h"

#include <QtSql/QSqlQuery>
#include <QVariant>

#include <algorithm>

#include "cdatabase.h"
#include "cbook.h"

CDatabaseAdapter::CDatabaseAdapter(QString filename)
{
    _db = new CDatabase;
    _db->open(filename);
}

CDatabaseAdapter::~CDatabaseAdapter()
{
    _db->close();
    delete _db;
}

QList<CBook> CDatabaseAdapter::readAll()
{
    QSqlQuery selectQuery(_db->instance());
    selectQuery.prepare("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog;");
    selectQuery.exec();

    QList<CBook> result;
    while(selectQuery.next())
    {
        auto id        = selectQuery.value(0).toInt();
        auto fullPath  = selectQuery.value(1).toString();
        auto name      = selectQuery.value(2).toString();
        auto extension = selectQuery.value(3).toString();
        auto size      = selectQuery.value(4).toInt();
        auto md5       = selectQuery.value(5).toByteArray();

        result.push_back(CBook(id, name, fullPath, extension, size, md5));
    }

    return result;
}

void CDatabaseAdapter::insert(const CBook &book)
{
    QSqlQuery insertQuery(_db->instance());
    insertQuery.prepare("INSERT INTO Catalog (Id, FullPath, Name, Extension, Size, MD5) VALUES(:Id, :FullPath,:Name,:Extension,:Size, :MD5);");

    insertQuery.bindValue(":Id", book.id());
    insertQuery.bindValue(":FullPath", book.fullPath());
    insertQuery.bindValue(":Name", book.name());
    insertQuery.bindValue(":Extension", book.extension());
    insertQuery.bindValue(":Size", book.size());
    insertQuery.bindValue(":MD5", book.md5());

    insertQuery.exec();
}

void CDatabaseAdapter::remove(const CBook &book)
{
    QSqlQuery removeQuery(_db->instance());
    auto removeQueryString = QString("DELETE FROM Catalog WHERE Id = %1;").arg(book.id());
    removeQuery.prepare(removeQueryString);

    removeQuery.bindValue(":FullPath", book.fullPath());
    removeQuery.bindValue(":Name", book.name());
    removeQuery.bindValue(":Extension", book.extension());
    removeQuery.bindValue(":Size", book.size());
    removeQuery.bindValue(":MD5", book.md5());

    removeQuery.exec();
}

void CDatabaseAdapter::update(const CBook &book)
{
    QSqlQuery updateQuery(_db->instance());
    auto updateQueryString = QString("UPDATE Catalog SET FullPath = :FullPath, Name = :Name, Extension = :Extension, Size = :Size, MD5 = :MD5 WHERE Id = %1;").arg(book.id());
    updateQuery.prepare(updateQueryString);

    updateQuery.bindValue(":FullPath", book.fullPath());
    updateQuery.bindValue(":Name", book.name());
    updateQuery.bindValue(":Extension", book.extension());
    updateQuery.bindValue(":Size", book.size());
    updateQuery.bindValue(":MD5", book.md5());

    updateQuery.exec();
}

void CDatabaseAdapter::saveChanges(const QList<CBook> &books)
{
    auto booksInDatabase = readAll();

    foreach (auto& item, booksInDatabase)
    {
        auto it = std::find_if(books.begin(), books.end(), [&] (const CBook &book)
        {
            return book.id() == item.id();
        });

        if(it == books.end())
        {
            remove(item);
        }
    }

    foreach (auto& item, books)
    {
        auto it = std::find_if(booksInDatabase.begin(), booksInDatabase.end(), [&] (const CBook &book)
        {
            return book.id() == item.id();
        });

        if(it == booksInDatabase.end())
        {
            insert(item);
            continue;
        }

        update(item);
    }
}








