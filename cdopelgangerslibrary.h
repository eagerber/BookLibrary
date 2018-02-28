#ifndef CDOPELGANGERSLIBRARY_H
#define CDOPELGANGERSLIBRARY_H

#include <QObject>

#include "cduplicatedbookrecord.h"

class QSqlDatabase;

class CDopelgangersLibrary : public QObject
{
    Q_OBJECT

public:
    explicit CDopelgangersLibrary();
    CDopelgangersLibrary(const CDopelgangersLibrary &rValue);

    ~CDopelgangersLibrary();

    void addItem(const CDuplicatedBookRecord &bookRecord);

    CDuplicatedBookRecord& last();
    CDuplicatedBookRecord& first();
    CDuplicatedBookRecord& at(const int index);

    int length();

    QStringList toStringList();

private:
    QList<CDuplicatedBookRecord> _items;
    QSqlDatabase *_database;

};

#endif // CDOPELGANGERSLIBRARY_H
