#include "cbooklist.h"


CBookList::CBookList()
    : CBook()
{

}

CBookList::CBookList(const CBookList &rValue)
    : CBook(rValue)
{
    _dopelgangers = rValue._dopelgangers;
}

CBookList::CBookList(const int id, const QString &name, const QString &fullPath)
    : CBook(id, name, fullPath)
{

}

void CBookList::addDuplicate(const CBook &duplicate)
{
    _dopelgangers.push_back(duplicate);
}

CBook& CBookList::at(const int index)
{
    return _dopelgangers[index];
}

QStringList CBookList::dopelgangersStringList()
{
    QStringList result;

    foreach (const auto &dopelganger, _dopelgangers)
    {
        result << dopelganger.fullPath();
    }

    return result;
}

