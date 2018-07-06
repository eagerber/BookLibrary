#include "automaticduplicatesprocessdialog.h"
#include "ui_automaticduplicatesprocessdialog.h"

#include <QStandardItemModel>

AutomaticDuplicatesProcessDialog::AutomaticDuplicatesProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutomaticDuplicatesProcessDialog)
{
    ui->setupUi(this);


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
