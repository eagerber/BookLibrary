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
    auto hash = book.md5();
    _data.insert(hash, book);
}

void CLibrary::remove(const CBook& book)
{
    auto bookHash = book.md5();
    _data.remove(bookHash, book);
}


void CLibrary::addRange(const QList<CBook>& books)
{
    for(int i = 0; i < books.length(); ++i)
    {
        add(books[i]);
    }
}

int CLibrary::count() const
{
    return _data.count();
}

const CBook& CLibrary::at(int n)
{
    return (_data.begin() + n).value();
}

int CLibrary::maxIndex()
{
    int id = 0;
    foreach(auto book, _data)
    {
        id = qMax(id, book.id());
    }

    return id;
}


QList<CBook*> CLibrary::data()
{
    QList<CBook*> bookList;

    for(LibraryMap::iterator it = _data.begin(); it != _data.end(); it++)
    {
        bookList.append(&it.value());
    }

    return bookList;
}

QList<CBook*> CLibrary::doppelgangers(const CBook& book)
{
    QList<CBook*> doppelgangersList;

    foreach(auto book, _data.values(book.md5()))
    {
        doppelgangersList.append(&book);
    }

    return doppelgangersList;
}

QList<CBook*> CLibrary::doppelgangers()
{
    QList<CBook*> doppelgangersList;

    foreach (auto hash, _data.keys())
    {
        auto books = _data.values(hash);
        if(books.count()  > 1)
        {
            doppelgangersList.append(&books[0]);
        }
    }

    return doppelgangersList;
}

void CLibrary::deleteDuplicates()
{
    QList<CBook*> fullDuplicates;

    foreach (auto hash, _data.keys())
    {
        auto books = _data.values(hash);
        for(int i = 0 ; i < books.length(); ++i)
        {
            for(int j = i+ 1; j < books.length(); ++j)
            {
                if(books[i].fullMatch(books[j]))
                {
                    fullDuplicates.append(&books[j]);
                }
            }
        }
    }

    foreach(auto book, fullDuplicates)
    {
        remove(*book);
    }
}

void CLibrary::normalize(const CBook &book, const QString truePath)
{
    //TODO: need to be simplified!
    auto bookList = _data.values(book.md5());
    QList<CBook> deleteList;
    for(int i = bookList.length() - 1; i > -1; --i)
    {
        auto currentBook = bookList.at(i);
        auto currentFullPath = currentBook.fullPath();
        if(currentFullPath != truePath)
        {
            deleteList.append(currentBook);
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
    book.setFullPath(fileInfo.absoluteFilePath());
}

void CLibrary::deleteFile(const QString &filename)
{
    Utils::deleteFile(filename);
}
















