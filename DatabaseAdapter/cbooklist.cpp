#include "cbooklist.h"


CBookList::CBookList()
    : CBook()
{

}

CBookList::CBookList(const CBookList &rValue)
    : CBook(rValue)
{
    _books = rValue._books;
}

CBookList::CBookList(const int id, const QString &name, const QString &fullPath)
    : CBook(id, name, fullPath)
{

}

void CBookList::addDuplicate(const CBook &duplicate)
{
    _books.push_back(duplicate);
}

const CBook& CBookList::at(const int index) const
{
    return _books[index];
}

int CBookList::length() const
{
    return _books.length();
}

QStringList CBookList::toStringList()
{
    QStringList result;

    foreach (const auto &dopelganger, _books)
    {
        result << dopelganger.fullPath();
    }

    return result;
}

