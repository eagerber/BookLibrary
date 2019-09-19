#ifndef CLIBRARY_H
#define CLIBRARY_H

#include <QList>
#include <QMap>

#include "cbook.h"

class CLibrary
{
public:
    CLibrary();

    void add(const CBook& book);

    // TODO: tests
    void addRange(const QList<CBook>& book);
    // TODO: tests
    int count();
    // TODO: tests
    CBook& operator[](int n);
    // TODO: tests
    const CBook& at(int n);
    // TODO: tests
    int maxIndex();
    // TODO: tests
    QList<CBook>& data();

    QList<CBook> doppelgangers(CBook& book);
    QList<CBook> doppelgangers();

private:
    QList<CBook> _data;
    QMap<QByteArray, QList<int>> _doppelgangers;
};

#endif // CLIBRARY_H
