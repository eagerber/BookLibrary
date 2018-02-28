#ifndef CDOPELGANGERSLIBRARY_H
#define CDOPELGANGERSLIBRARY_H

#include <QObject>

#include "cbooklist.h"

class QSqlDatabase;

class CDopelgangersLibrary : public QObject
{
    Q_OBJECT

public:
    explicit CDopelgangersLibrary();
    CDopelgangersLibrary(const CDopelgangersLibrary &rValue);

    ~CDopelgangersLibrary();

    void addItem(const CBookList &bookRecord);

    CBookList& last();
    CBookList& first();
    CBookList& at(const int index);

    int length();

    QStringList toStringList();

private:
    QList<CBookList> _items;
    QSqlDatabase *_database;

};

#endif // CDOPELGANGERSLIBRARY_H
