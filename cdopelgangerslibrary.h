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

    void init();

    void addItem(const CBookList &bookRecord);

    CBookList& last();
    CBookList& first();
    CBookList& at(const int index);
    CBook& at(const int booksListIndex, const int bookIndex);

    int length();

    QStringList books();
    QStringList duplicatesByIndex(const int index);

    // Delete doppelgangers for bookListIndex set
    void normalize(const int booksListIndex, const int trueBookIndex = 0);
    void normalize();

private:
    void deleteFile(const QString &filename);
    void deleteFromDb(const int id);

    QList<CBookList> _booksList;

};

#endif // CDOPELGANGERSLIBRARY_H
