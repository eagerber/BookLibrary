#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class BookLibraryModel;

class ProxyBookLibraryModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ProxyBookLibraryModel(BookLibraryModel *model, QObject* parent = nullptr);
    virtual ~ProxyBookLibraryModel();

    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

public slots:
    void setFullPath(QString fullPath);
    void setName(QString name);
    void setExtension(QString extension);
private:
    QString _fullPath;
    QString _name;
    QString _extension;
};

#endif // PROXYMODEL_H
