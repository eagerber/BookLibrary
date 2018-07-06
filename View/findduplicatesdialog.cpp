#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QDebug>

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

void FindDuplicatesDialog::init()
{

    _ui->inspectedFiles->setCurrentIndex(_inspectedModel->index(0));
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
