#ifndef DATABASEADAPTER_H
#define DATABASEADAPTER_H

#include <QList>

#include "cbook.h"

class CDatabase;
class QSqlQuery;

class CDatabaseAdapter
{
public:
    CDatabaseAdapter(QString filename);
    ~CDatabaseAdapter();

    QList<CBook> ReadAll();

    void Insert(const CBook &book);
    void InsertAll(const QList<CBook> &books);

private:
    void internalInsert(QSqlQuery &query, const CBook& book);

    CDatabase *_db;
};

#endif // DATABASEADAPTER_H
