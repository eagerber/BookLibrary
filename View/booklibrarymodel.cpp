#include "booklibrarymodel.h"

#include "cbook.h"
#include "cdatabaseadapter.h"
#include "clibrary.h"

BookLibraryModel::BookLibraryModel(QString databaseFilename, QObject* parent)
    : QAbstractTableModel(parent)
{
    _databaseFilename = databaseFilename;

    _library = new CLibrary();
}

BookLibraryModel::BookLibraryModel() {}

BookLibraryModel::~BookLibraryModel() {}

void BookLibraryModel::init()
{
    auto adapter = new CDatabaseAdapter(_databaseFilename);

    _library->addRange(adapter->readAll());

    delete adapter;
}

int BookLibraryModel::rowCount(const QModelIndex &parent) const
{
    return _library->count();
}

int BookLibraryModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant BookLibraryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= _library->count() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        auto &book = _library->at(index.row());
        if(index.column() == 0)
        {
            return book.name();
        }
        if(index.column() == 1)
        {
            return book.fullPath();
        }
        if(index.column() == 2)
        {
            return book.extension();
        }
        if(index.column() == 3)
        {
            return book.size();
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignLeft;
    }
    return QVariant();
}

QVariant BookLibraryModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("FullFath");
        case 2:
            return tr("Extension");
        case 3:
            return tr("Size");
        default:
            return QVariant();
        }
    }
    return section + 1;
}

void BookLibraryModel::add(const CBook &book)
{
    _library->add(book);

    emit dataChanged(index(_library->count() - 1, 0), index(_library->count() - 1, 6));
}

int BookLibraryModel::maxIndex()
{
    return _library->maxIndex();
}

void BookLibraryModel::saveChanges()
{
    auto adapter = new CDatabaseAdapter(_databaseFilename);

    adapter->saveChanges(_library->data());

    delete adapter;
};

QString BookLibraryModel::filename()
{
    return _databaseFilename;
}

CLibrary& BookLibraryModel::library()
{
    return *_library;
}




