#ifndef REPLACEBYEXTENSIONDIALOG_H
#define REPLACEBYEXTENSIONDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

class CLibrary;
class CBook;

namespace Ui {
class ReplaceByExtensionDialog;
}

class ReplaceByExtensionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceByExtensionDialog(CLibrary &library, QWidget *parent = nullptr);
    ~ReplaceByExtensionDialog();

private slots:

    void on_replacePushButton_clicked();

    void on_destinationFolderToolButton_clicked();

    void on_destinationFolderLineEdit_returnPressed();

    void on_ReplaceByExtensionDialog_accepted();

private:
    void initModel();

    Ui::ReplaceByExtensionDialog *ui;

    QStandardItemModel *_model;

    CLibrary &_library;
    QList<QPair<int, QString>> _replacement;
};

#endif // REPLACEBYEXTENSIONDIALOG_H
