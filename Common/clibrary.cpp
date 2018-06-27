#include "clibrary.h"

#include <QSet>

CLibrary::CLibrary()
{

}

void CLibrary::add(const CBook& book)
{
    _bookList.push_back(book);
}

QList<CBook> CLibrary::doppelgangers(const CBook& book)
{
    QList<CBook> result;

    foreach (const auto& item, _bookList)
    {
        if(book.HashSumMatch(item))
        {
            result.push_back(item);
        }
    }

    return result;
}

QList<QList<CBook>> CLibrary::allDoppelgangers()
{
    QSet<CBook> uniqueBooks = _bookList.toSet();

    QList<QList<CBook>> result;

    foreach (const auto& item, uniqueBooks)
    {
        auto currentDoppelgangers = doppelgangers(item);
        result.push_back(currentDoppelgangers);
    }

    return result;
}
