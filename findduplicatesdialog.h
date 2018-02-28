#ifndef FINDDUPLICATESDIALOG_H
#define FINDDUPLICATESDIALOG_H

#include <QDialog>

#include <QSqlDatabase>
#include <QStringListModel>
#include <QItemSelection>
#include <QList>


namespace Ui {
class FindDuplicatesDialog;
}

class CDopelgangersLibrary;

class FindDuplicatesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDuplicatesDialog(QWidget *parent = 0);    
    ~FindDuplicatesDialog();

private slots:
    void inspectedFilesSelectionChanged(const QItemSelection& selection);

    void on_inspectedCopiesList_doubleClicked(const QModelIndex &index);

    void on_deleteDuplicatesBtn_clicked();

private:
    void init();

    Ui::FindDuplicatesDialog *_ui;

    QStringListModel *_inspectedModel;
    QStringListModel *_inspectedCopiesModel;

    CDopelgangersLibrary *_library;
};

#endif // FINDDUPLICATESDIALOG_H
