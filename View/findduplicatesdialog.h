#ifndef FINDDUPLICATESDIALOG_H
#define FINDDUPLICATESDIALOG_H

#include <QDialog>

#include <QStringListModel>
#include <QItemSelection>
#include <QList>

class CLibrary;
class CBook;

namespace Ui {
class FindDuplicatesDialog;
}

class CDopelgangersLibrary;

class FindDuplicatesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDuplicatesDialog(CLibrary &library, QWidget *parent = nullptr);
    ~FindDuplicatesDialog();

private slots:
    void inspectedFilesSelectionChanged(const QItemSelection& selection);

    void on_inspectedCopiesList_doubleClicked(const QModelIndex &index);

    void on_deleteDuplicatesBtn_clicked();

private:
    void init();
    void fillCopies(int bookIndex);

    Ui::FindDuplicatesDialog *_ui;

    QStringListModel *_inspectedModel;
    QStringListModel *_inspectedCopiesModel;

    CLibrary &_library;
    QList<CBook> _doppelgangers;
};

#endif // FINDDUPLICATESDIALOG_H
