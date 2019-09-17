#include "proxybooklibrarymodel.h"

#include "booklibrarymodel.h"

ProxyBookLibraryModel::ProxyBookLibraryModel(BookLibraryModel *model, QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(model);
}

ProxyBookLibraryModel::~ProxyBookLibraryModel() {}

bool ProxyBookLibraryModel::filterAcceptsRow(int source_row,
                      const QModelIndex &source_parent) const
{
    if(_name.isEmpty() && _fullPath.isEmpty() && _extension.isEmpty()) return true;

    QModelIndex indName = sourceModel()->index(source_row, 0, source_parent);
    QModelIndex indFullpath = sourceModel()->index(source_row, 1, source_parent);
    QModelIndex indExtension = sourceModel()->index(source_row, 2, source_parent);

    if(!_name.isEmpty() && sourceModel()->data(indName).toString().contains(_name)) return true;
    if(!_fullPath.isEmpty() && sourceModel()->data(indFullpath).toString().contains(_fullPath)) return true;
    if(!_extension.isEmpty() && sourceModel()->data(indExtension).toString().contains(_extension)) return true;

    return false;
}
QVariant ProxyBookLibraryModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    return sourceModel()->headerData(section, orientation, role);
}

void ProxyBookLibraryModel::setFullPath(QString fullPath)
{
    if(_fullPath != fullPath)
        _fullPath = fullPath;
    invalidateFilter();
}

void ProxyBookLibraryModel::setName(QString name)
{
    if(_name != name)
        _name = name;
    invalidateFilter();
}

void ProxyBookLibraryModel::setExtension(QString extension)
{
    if(_extension != extension)
        _extension = extension;
    invalidateFilter();
}
