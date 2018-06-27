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
    QSet<QByteArray> uniqueHashes;

    QList<QList<CBook>> result;

    foreach (const auto& item, _bookList)
    {
        if(uniqueHashes.contains(item.md5()))
        {
            continue;
        }

        auto currentDoppelgangers = doppelgangers(item);
        if(currentDoppelgangers.length() > 1)
        {
            result.push_back(currentDoppelgangers);
            uniqueHashes += currentDoppelgangers[0].md5();
        }
    }

    return result;
}
