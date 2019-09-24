#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QDebug>

#include "clibrary.h"

FindDuplicatesDialog::FindDuplicatesDialog(CLibrary &library, QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::FindDuplicatesDialog),
    _library(library)
{
    _ui->setupUi(this);

    _inspectedModel = new QStringListModel();
    _inspectedCopiesModel = new QStringListModel();

    _ui->inspectedFiles->setModel(_inspectedModel);
    _ui->inspectedCopiesList->setModel(_inspectedCopiesModel);

    connect(_ui->inspectedFiles->selectionModel(),
       SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
       this, SLOT(inspectedFilesSelectionChanged(QItemSelection)));

    init();
}

void FindDuplicatesDialog::init()
{
    _doppelgangers = _library.doppelgangers();

    if(_doppelgangers.length() == 0) return;

    QStringList inspected;
    for(int i = 0; i < _doppelgangers.length(); ++i)
    {
        inspected.append(_doppelgangers[i].name());
    }
    _inspectedModel->setStringList(inspected);

    _ui->inspectedFiles->setModel(_inspectedModel);

    fillCopies(0);

    _ui->inspectedFiles->setCurrentIndex(_inspectedModel->index(0));
}

void FindDuplicatesDialog::fillCopies(int bookIndex)
{
    QStringList inspectedCopies;
    QList<CBook> currentCopies = _library.doppelgangers(_doppelgangers[bookIndex]);
    for(int i = 0; i < currentCopies.length(); ++i)
    {
        inspectedCopies.append(currentCopies[i].fullPath());
    }

    _inspectedCopiesModel->setStringList(inspectedCopies);
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    delete _inspectedModel;
    delete _inspectedCopiesModel;
    delete _ui;
}

void FindDuplicatesDialog::inspectedFilesSelectionChanged(const QItemSelection& selection)
{
    int row = selection.indexes().first().row();
    fillCopies(row);
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

    int booksListIndex = _ui->inspectedFiles->selectionModel()->currentIndex().row();
    int trueBookIndex = _ui->inspectedCopiesList->selectionModel()->currentIndex().row();


}
