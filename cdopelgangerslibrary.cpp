#include "cdopelgangerslibrary.h"

CDopelgangersLibrary::CDopelgangersLibrary()
    : QObject()
{
}

CDopelgangersLibrary::CDopelgangersLibrary(const CDopelgangersLibrary &rValue)
    : CDopelgangersLibrary()
{
    _items = rValue._items;
    _database = rValue._database;
}

CDopelgangersLibrary::~CDopelgangersLibrary()
{

}

void CDopelgangersLibrary::addItem(const CBookList &bookRecord)
{
    _items.push_back(bookRecord);
}


CBookList& CDopelgangersLibrary::last()
{
    return _items.last();
}

CBookList& CDopelgangersLibrary::first()
{
    return _items.first();
}

CBookList& CDopelgangersLibrary::at(const int index)
{
    return _items[index];
}

int CDopelgangersLibrary::length()
{
    return _items.length();
}

QStringList CDopelgangersLibrary::toStringList()
{
    QStringList result;

    foreach (const auto &book, _items)
    {
        result << book.name();
    }

    return result;
}
