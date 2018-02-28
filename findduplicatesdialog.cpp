#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

#include <QSqlQuery>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QDebug>

#include "Windows.h"
#include "shellapi.h"

struct CBookRecord
{
    int _id;
    QString _name;
    QString _fullPath;

    CBookRecord(const int id, const QString &name, const QString &fullPath)
    {
        _id = id;
        _name = name;
        _fullPath = fullPath;
    }
};

struct CDuplicatedBookRecord : public CBookRecord
{
    QList<CBookRecord> _dopelgangers;

    QStringList dopelgangersStringList()
    {
        QStringList result;

        foreach (const auto &dopelganger, _dopelgangers)
        {
            result << dopelganger._fullPath;
        }

        return result;
    }

    CDuplicatedBookRecord(const int id, const QString &name, const QString &fullPath)
        : CBookRecord(id, name, fullPath)
    {

    }
};

struct CDopelgangersLibrary
{
    QList<CDuplicatedBookRecord> _items;

    QStringList toStringList()
    {
        QStringList result;

        foreach (const auto &book, _items)
        {
            result << book._name;
        }

        return result;
    }
};

FindDuplicatesDialog::FindDuplicatesDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::FindDuplicatesDialog)
{
    _ui->setupUi(this);

    _inspectedModel = new QStringListModel();
    _inspectedCopiesModel = new QStringListModel();

    _ui->inspectedFiles->setModel(_inspectedModel);
    _ui->inspectedCopiesList->setModel(_inspectedCopiesModel);

    connect(_ui->inspectedFiles->selectionModel(),
       SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
       this, SLOT(inspectedFilesSelectionChanged(QItemSelection)));
}

FindDuplicatesDialog::FindDuplicatesDialog(QWidget *parent, QSqlDatabase *database) :
    FindDuplicatesDialog(parent)
{
    _database = database;
    _library = new CDopelgangersLibrary();

    init();
}

void FindDuplicatesDialog::init()
{
    if(_library != nullptr)
    {
        delete _library;
    }
    _library = new CDopelgangersLibrary();

    QSqlQuery query;
    query.exec("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog c2 WHERE ( SELECT COUNT(*) FROM Catalog c1 WHERE c1.MD5 = c2.MD5 ) > 1 ORDER BY MD5;");

    QByteArray prevMd5;
    int prevSize = -1;
    int currentItem = -1;
    while (query.next())
    {
        QByteArray currentMd5 = query.value(5).toByteArray();
        int currentSize = query.value(4).toInt();

        QString name = query.value(2).toString();
        QString fullPath = query.value(1).toString();
        int id = query.value(0).toInt();

        if ((prevMd5 != currentMd5) || (prevSize != currentSize))
        {
            currentItem++;

            _library->_items.push_back(CDuplicatedBookRecord(id, name, fullPath));
        }
        _library->_items.last()._dopelgangers.push_back(CBookRecord(id, name, fullPath));

        prevMd5 = currentMd5;
        prevSize = currentSize;
    }

    query.clear();

    _bookList = _library->toStringList();
    if (_library->_items.length() > 0)
    {
        _dopelgangersList = _library->_items.first().dopelgangersStringList();
    }
    else
    {
        _dopelgangersList = QStringList();
    }

    _inspectedModel->setStringList(_bookList);
    _inspectedCopiesModel->setStringList(_dopelgangersList);

    _ui->inspectedFiles->setCurrentIndex(_inspectedModel->index(0));
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    _database = nullptr;
    delete _library;
    delete _inspectedModel;
    delete _inspectedCopiesModel;
    delete _ui;
}

void FindDuplicatesDialog::inspectedFilesSelectionChanged(const QItemSelection& selection)
{
    int row = selection.indexes().first().row();
    _dopelgangersList = _library->_items[row].dopelgangersStringList();

    _inspectedCopiesModel->setStringList(_dopelgangersList);
}

void FindDuplicatesDialog::on_inspectedCopiesList_doubleClicked(const QModelIndex &index)
{
    QString path = _inspectedCopiesModel->stringList().at(index.row());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void FindDuplicatesDialog::on_deleteDuplicatesBtn_clicked()
{
    if(_ui->inspectedCopiesList->selectionModel()->selection().empty())
    {
        QMessageBox::question(this, "Warning", "Please choose book source from right listbox.", QMessageBox::Ok);
        return;
    }

    int sourceIndex = _ui->inspectedCopiesList->selectionModel()->currentIndex().row();

    auto &sourceFile = _dopelgangersList.at(sourceIndex);

    for(int i = _dopelgangersList.length() - 1; i > -1; --i)
    {
        if(i == sourceIndex)
        {
            continue;
        }

        int row = _ui->inspectedFiles->selectionModel()->currentIndex().row();
        deleteFromDb(_library->_items[row]._dopelgangers[i]._id);

        if(_dopelgangersList[i] != sourceFile)
        {
            deleteFile(_dopelgangersList[i]);
        }
    }

    init();
}

void FindDuplicatesDialog::deleteFile(const QString &filename)
{
    //QFile file(filename);
    //file.remove();

    // Move to recycle bin
    LPCSTR lpcFrom = (LPCSTR)filename.toLocal8Bit().constData();

    SHFILEOPSTRUCTA operation;

    operation.wFunc = FO_DELETE;
    operation.pFrom = lpcFrom;
    operation.fFlags = FOF_ALLOWUNDO|FOF_NO_UI|FOF_NORECURSION;

    int result = SHFileOperationA(&operation);

    qDebug() << filename << result;
}

void FindDuplicatesDialog::deleteFromDb(const int id)
{
    QString query = QString("DELETE FROM Catalog WHERE Id = %1").arg(id);

    _database->exec(query);
    _database->commit();
}








