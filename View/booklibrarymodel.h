#ifndef BOOKLIBRARYMODEL_H
#define BOOKLIBRARYMODEL_H

#include <QAbstractTableModel>


class CBook;
class CLibrary;

class BookLibraryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    BookLibraryModel(QString databaseFilename, QObject* parent = nullptr);
    virtual ~BookLibraryModel() override;

    void init();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void add(const CBook& book);
    int maxIndex();
    void saveChanges();
    QString filename();

private:
    BookLibraryModel();

    CLibrary *_library;
    QString _databaseFilename;
};


#endif // BOOKLIBRARYMODEL_H
