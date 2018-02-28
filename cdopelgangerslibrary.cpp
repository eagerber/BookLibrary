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

void CDopelgangersLibrary::addItem(const CDuplicatedBookRecord &bookRecord)
{
    _items.push_back(bookRecord);
}


CDuplicatedBookRecord& CDopelgangersLibrary::last()
{
    return _items.last();
}

CDuplicatedBookRecord& CDopelgangersLibrary::first()
{
    return _items.first();
}

CDuplicatedBookRecord& CDopelgangersLibrary::at(const int index)
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
