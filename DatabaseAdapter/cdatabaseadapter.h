#ifndef DATABASEADAPTER_H
#define DATABASEADAPTER_H

#include <QList>

class CDatabase;
class QSqlQuery;
class CBook;

class CDatabaseAdapter
{
public:
    CDatabaseAdapter(QString filename);
    ~CDatabaseAdapter();

    QList<CBook> readAll();

    void insert(const CBook &book);
    void update(const CBook &book);

    void saveChanges(const QList<CBook> &books);

private:
    CDatabase *_db;
};

#endif // DATABASEADAPTER_H
