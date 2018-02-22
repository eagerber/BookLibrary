#include "automaticduplicatesprocessdialog.h"
#include "ui_automaticduplicatesprocessdialog.h"

AutomaticDuplicatesProcessDialog::AutomaticDuplicatesProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutomaticDuplicatesProcessDialog)
{
    ui->setupUi(this);
}

AutomaticDuplicatesProcessDialog::~AutomaticDuplicatesProcessDialog()
{
    delete ui;
}
