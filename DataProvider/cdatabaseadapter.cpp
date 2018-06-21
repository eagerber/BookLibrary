#include "cdatabaseadapter.h"

#include <QtSql/QSqlQuery>
#include <QVariant>

#include "cdatabase.h"

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

QList<CBook> CDatabaseAdapter::ReadAll()
{
    QSqlQuery selectQuery(_db->instance());
    selectQuery.prepare("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog ORDER BY Id;");

    QList<CBook> result;
    while(selectQuery.next())
    {
        auto id        = selectQuery.value(0).toInt();
        auto fullPath  = selectQuery.value(1).toString();
        auto name      = selectQuery.value(2).toString();
        auto extension = selectQuery.value(3).toString();
        auto size      = selectQuery.value(4).toInt();
        auto md5       = selectQuery.value(5).toByteArray();

        result.push_back(CBook(id, fullPath, name, extension, size, md5));
    }

    return result;
}

void CDatabaseAdapter::Insert(const CBook &book)
{
    QSqlQuery insertQuery(db.instance());
    insertQuery.prepare("INSERT INTO Catalog (Id, FullPath, Name, Extension, Size, MD5) VALUES(:Id, :FullPath,:Name,:Extension,:Size, :MD5);");

    internalInsert(insertQuery, book);
}

void CDatabaseAdapter::InsertAll(const QList<CBook> &books)
{
    QSqlQuery insertQuery(db.instance());
    insertQuery.prepare("INSERT INTO Catalog (Id, FullPath, Name, Extension, Size, MD5) VALUES(:Id, :FullPath,:Name,:Extension,:Size, :MD5);");

    foreach (auto& item, books)
    {
        internalInsert(insertQuery, book);
    }
}

void CDatabaseAdapter::internalInsert(QSqlQuery &query, const CBook& book)
{
    insertQuery.bindValue(":Id", book.id());
    insertQuery.bindValue(":FullPath", book.fullPath());
    insertQuery.bindValue(":Name", book.name());
    insertQuery.bindValue(":Extension", book.extension());
    insertQuery.bindValue(":Size", book.size());
    insertQuery.bindValue(":MD5", book.md5());

    insertQuery.exec();
}
