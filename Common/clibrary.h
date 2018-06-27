#ifndef CLIBRARY_H
#define CLIBRARY_H

#include <QList>
#include "cbook.h"

class CLibrary
{
public:
    CLibrary();

    void add(const CBook& book);

    QList<CBook> doppelgangers(const CBook& book);

    QList<QList<CBook>> allDoppelgangers();


private:
    QList<CBook> _bookList;
};

#endif // CLIBRARY_H
