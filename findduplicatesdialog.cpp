#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

#include <QSqlQuery>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>

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

    QSqlQuery query;
    query.exec("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog c2 WHERE ( SELECT COUNT(*) FROM Catalog c1 WHERE c1.MD5 = c2.MD5 ) > 1 ORDER BY MD5 ");

    QStringList inspectedData;

    QByteArray prevMd5;
    int currentItem = -1;
    while (query.next())
    {
        QByteArray currentMd5 = query.value(5).toByteArray();

        QString name = query.value(2).toString();
        QString fullPath = query.value(1).toString();

        if (prevMd5 != currentMd5)
        {
            currentItem++;
            inspectedCopiesData.push_back(QStringList());

            inspectedData << name;
        }
        inspectedCopiesData[currentItem] << fullPath;

        prevMd5 = currentMd5;
    }

    query.clear();

    _inspectedModel->setStringList(inspectedData);
    _inspectedCopiesModel->setStringList(inspectedCopiesData[0]);

    _ui->inspectedFiles->setCurrentIndex(_inspectedModel->index(0));
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    _database = nullptr;
    delete _inspectedModel;
    delete _inspectedCopiesModel;
    delete _ui;
}

void FindDuplicatesDialog::inspectedFilesSelectionChanged(const QItemSelection& selection)
{
    int row = selection.indexes().first().row();
    _inspectedCopiesModel->setStringList(inspectedCopiesData[row]);
    _ui->inspectedCopiesList->setModel(_inspectedCopiesModel);
}

void FindDuplicatesDialog::on_inspectedCopiesList_doubleClicked(const QModelIndex &index)
{
    QString path = _inspectedCopiesModel->stringList().at(index.row());
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
