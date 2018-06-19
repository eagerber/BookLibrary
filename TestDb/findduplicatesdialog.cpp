#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

FindDuplicatesDialog::FindDuplicatesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDuplicatesDialog)
{
    ui->setupUi(this);
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    delete ui;
}
