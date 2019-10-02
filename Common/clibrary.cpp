#include "clibrary.h"

#include <algorithm>

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>

#include "utils.h"

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

    auto& bookList = _doppelgangers[book.md5()];

    for(int i = 0; i < bookList.length(); ++i)
    {
        result.push_back(*bookList[i]);
    }

    return result;
}

QList<CBook> CLibrary::doppelgangers()
{
    QList<CBook> result;

    foreach (auto& bookList, _doppelgangers)
    {
        if(bookList.length() > 1)
        {
            result.append(*bookList[0]);
        }
    }

    return result;
}

void CLibrary::deleteDuplicates()
{
    QList<CBook> fullDuplicates;
    foreach(auto& bookList, _doppelgangers)
    {
        for(int i = 0 ; i < bookList.length(); ++i)
        {
            for(int j = i+ 1; j < bookList.length(); ++j)
            {
                if(bookList[i]->fullMatch(*bookList[j]))
                {
                    fullDuplicates.append(*bookList[j]);
                }
            }
        }
    }

    foreach(auto book, fullDuplicates)
    {
        remove(book);
    }
}

void CLibrary::normalize(const CBook &book, const QString truePath)
{
    //TODO: need to be simplified!
    auto bookList = _doppelgangers[book.md5()];
    QList<CBook> deleteList;
    for(int i = bookList.length() - 1; i > -1; --i)
    {
        auto currentBook = bookList.at(i);
        auto currentFullPath = currentBook->fullPath();
        if(currentFullPath != truePath)
        {
            deleteList.append(*currentBook);
            deleteFile(currentFullPath);
        }
    }

    foreach(auto book, deleteList)
    {
        remove(book);
    }
}

void CLibrary::removeNonExistentFiles()
{
    //TODO: need to be simplified!
    QList<CBook> deleteList;
    foreach(auto book, _data)
    {
        if(QFile::exists(book.fullPath())) continue;

        deleteList.append(book);
    }

    foreach(auto book, deleteList)
    {
        remove(book);
    }
}

QStringList CLibrary::availableExtensions()
{
    QStringList extensions;
    foreach(auto book, _data)
    {
        if(extensions.contains(book.extension())) continue;

        extensions.append(book.extension());
    }

    return extensions;
}

void CLibrary::replaceBook(CBook& book, QString path, bool deleteSource)
{
    auto fileInfo = Utils::replaceFile(book.fullPath(), path);
    if(deleteSource)
    {
        deleteFile(book.fullPath());
    }
    book.setName(fileInfo.fileName());
    book.setFullPath(fileInfo.absolutePath());
}

void CLibrary::deleteFile(const QString &filename)
{
    Utils::deleteFile(filename);
}
















