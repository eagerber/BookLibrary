#ifndef AUTOMATICDUPLICATESPROCESSDIALOG_H
#define AUTOMATICDUPLICATESPROCESSDIALOG_H

#include <QDialog>

#include <QStandardItemModel>


namespace Ui {
class AutomaticDuplicatesProcessDialog;
}

class AutomaticDuplicatesProcessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutomaticDuplicatesProcessDialog(QWidget *parent = 0);
    ~AutomaticDuplicatesProcessDialog();

private:
    Ui::AutomaticDuplicatesProcessDialog *ui;

    QStandardItemModel *_model;
};

#endif // AUTOMATICDUPLICATESPROCESSDIALOG_H
