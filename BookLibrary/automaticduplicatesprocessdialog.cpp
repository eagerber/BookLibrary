#include "automaticduplicatesprocessdialog.h"
#include "ui_automaticduplicatesprocessdialog.h"

#include <QStandardItemModel>

AutomaticDuplicatesProcessDialog::AutomaticDuplicatesProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutomaticDuplicatesProcessDialog)
{
    ui->setupUi(this);

    _library = new CDopelgangersLibrary();
    _library->init();

    _model = new QStandardItemModel (_library->totalLength(), 1);

    for(int i = 0; i < _library->length(); ++i)
    {
        QStandardItem *item = new QStandardItem(_library->at(i, 0).fullPath());

        for(int j = 1; j < _library->at(i).length(); ++j)
        {
            QStandardItem *child = new QStandardItem(_library->at(i, j).fullPath());
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
