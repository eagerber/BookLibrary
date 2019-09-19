#include "clibrary.h"

CLibrary::CLibrary()
{
}

void CLibrary::add(const CBook& book)
{
    _data.append(book);

    auto hash = book.md5();
    if(!_doppelgangers.contains(hash))
    {
        _doppelgangers.insert(hash, QList<int>());
    }

    int currentIndex = _data.length() - 1;
    _doppelgangers[hash].push_back(currentIndex);
}

void CLibrary::addRange(const QList<CBook>& books)
{
    for(int i = 0; i < books.length(); ++i)
    {
        add(books[i]);
    }
}

int CLibrary::count()
{
    return _data.length();
}

CBook& CLibrary::operator[](int n)
{
    return _data[n];
}

const CBook& CLibrary::at(int n)
{
    return _data[n];
}

int CLibrary::maxIndex()
{
    int id = 0;
    for(int i = 0; i < _data.length(); ++i)
    {
        id = std::max(id, _data[i].id());
    }

    return id;
}


QList<CBook>& CLibrary::data()
{
    return _data;
}

QList<CBook> CLibrary::doppelgangers(CBook& book)
{
    QList<CBook> result;

    auto& indecies = _doppelgangers[book.md5()];

    for(int i = 0; i < indecies.length(); ++i)
    {
        result.push_back(_data[indecies[i]]);
    }

    return result;
}

QList<CBook> CLibrary::doppelgangers()
{
    QList<CBook> result;

    foreach (auto& indeciesList, _doppelgangers)
    {
        if(indeciesList.length() > 1)
        {
            result.append(_data[indeciesList[0]]);
        }
    }

    return result;
}
