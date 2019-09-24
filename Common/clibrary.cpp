#include "clibrary.h"

#include <algorithm>

CLibrary::CLibrary()
{
}

void CLibrary::add(const CBook& book)
{
    _data.append(book);

    auto hash = book.md5();
    if(!_doppelgangers.contains(hash))
    {
        _doppelgangers.insert(hash, QList<CBook*>());
    }

    _doppelgangers[hash].push_back(&_data.last());
}

void CLibrary::remove(const CBook& book)
{
    auto bookHash = book.md5();
    if(!_doppelgangers.contains(bookHash)) return;

    int indexInList = _data.indexOf(book);
    int doppelgangerIndex = _doppelgangers[bookHash].indexOf(&_data[indexInList]);

    _doppelgangers[bookHash].removeAt(doppelgangerIndex);

    if(_doppelgangers[bookHash].length() == 0)
    {
        _doppelgangers.remove(bookHash);
    }

    _data.removeAt(indexInList);
}

void CLibrary::remove(int index)
{
    if(index > _data.length()) return;

    remove(_data[index]);
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
        result.push_back(*indecies[i]);
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
            result.append(*indeciesList[0]);
        }
    }

    return result;
}

void CLibrary::deleteDuplicates()
{
    QList<CBook> fullDuplicates;
    foreach(auto& indeciesList, _doppelgangers)
    {
        for(int i = 0 ; i < indeciesList.length(); ++i)
        {
            for(int j = 1 ; j < indeciesList.length(); ++j)
            {
                if(indeciesList[i] == indeciesList[j])
                {
                    fullDuplicates.append(*indeciesList[j]);
                }
            }
        }
    }

    foreach(auto book, fullDuplicates)
    {
        remove(book);
    }
}





