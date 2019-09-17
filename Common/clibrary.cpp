#include "clibrary.h"

#include <QSet>

CLibrary::CLibrary()
{

}

void CLibrary::add(const CBook& book)
{
    _bookList.push_back(book);
}


void CLibrary::addRange(const QList<CBook>& books)
{
    foreach (const auto& book, books)
    {
        _bookList.push_back(book);
    }
}

int CLibrary::count()
{
    return _bookList.count();
}

CBook& CLibrary::operator[](int n)
{
    return _bookList[n];
}

const CBook& CLibrary::at(int n)
{
    return _bookList[n];
}

int CLibrary::maxIndex()
{
    int id = 0;
    foreach(auto& item, _bookList)
    {
        id = std::max(id, item.id());
    }

    return id;
}

QList<CBook>& CLibrary::data()
{
    return _bookList;
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
