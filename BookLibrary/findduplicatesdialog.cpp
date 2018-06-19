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

#include "cdopelgangerslibrary.h"

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
    _library->init();

    _inspectedModel->setStringList(_library->books());
    _inspectedCopiesModel->setStringList(_library->duplicatesByIndex(0));

    _ui->inspectedFiles->setCurrentIndex(_inspectedModel->index(0));
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    delete _library;
    delete _inspectedModel;
    delete _inspectedCopiesModel;
    delete _ui;
}

void FindDuplicatesDialog::inspectedFilesSelectionChanged(const QItemSelection& selection)
{
    int row = selection.indexes().first().row();

    _inspectedCopiesModel->setStringList(_library->duplicatesByIndex(row));
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

    _library->normalize(booksListIndex, trueBookIndex);

    init();
}
