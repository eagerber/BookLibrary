#ifndef AUTOMATICDUPLICATESPROCESSDIALOG_H
#define AUTOMATICDUPLICATESPROCESSDIALOG_H

#include <QDialog>

#include <QStandardItemModel>

class CLibrary;
class CBook;

namespace Ui {
class AutomaticDuplicatesProcessDialog;
}

class AutomaticDuplicatesProcessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutomaticDuplicatesProcessDialog(CLibrary &library, QWidget *parent = 0);
    ~AutomaticDuplicatesProcessDialog();

private:
    Ui::AutomaticDuplicatesProcessDialog *ui;

    QStandardItemModel *_model;

    CLibrary &_library;
    QList<CBook> _doppelgangers;
};

#endif // AUTOMATICDUPLICATESPROCESSDIALOG_H
