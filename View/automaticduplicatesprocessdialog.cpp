#include "automaticduplicatesprocessdialog.h"
#include "ui_automaticduplicatesprocessdialog.h"

#include <QStandardItemModel>

#include "clibrary.h"

AutomaticDuplicatesProcessDialog::AutomaticDuplicatesProcessDialog(CLibrary &library, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutomaticDuplicatesProcessDialog),
    _library(library)
{
    ui->setupUi(this);

    _model = new QStandardItemModel(_library.data().length(), 1);

    auto doppelgangers = _library.doppelgangers();

    for(int i = 0; i < doppelgangers.length(); ++i)
    {
        auto currentBookList = _library.doppelgangers(doppelgangers[i]);
        QStandardItem *item = new QStandardItem(currentBookList.at(0).fullPath());

        for(int j = 1; j < currentBookList.length(); ++j)
        {
            QStandardItem *child = new QStandardItem(currentBookList.at(j).fullPath());
            child->setEditable( false );
            child->setForeground(QBrush(Qt::GlobalColor::red));
            item->appendRow(child);
        }
        _model->setItem(i, 0, item);
    }


    ui->treeView->setModel(_model);
    ui->treeView->header()->hide();
    ui->treeView->expandAll();

    ui->automaticDeleteCopiesBtn->setEnabled(false);
}

AutomaticDuplicatesProcessDialog::~AutomaticDuplicatesProcessDialog()
{
    delete _model;
    delete ui;
}
