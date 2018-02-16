#ifndef FINDDUPLICATESDIALOG_H
#define FINDDUPLICATESDIALOG_H

#include <QDialog>

namespace Ui {
class FindDuplicatesDialog;
}

class FindDuplicatesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDuplicatesDialog(QWidget *parent = 0);
    ~FindDuplicatesDialog();

private:
    Ui::FindDuplicatesDialog *ui;
};

#endif // FINDDUPLICATESDIALOG_H
