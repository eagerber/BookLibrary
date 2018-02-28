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
    explicit FindDuplicatesDialog(QWidget *parent, QSqlDatabase *database);
    ~FindDuplicatesDialog();

private slots:
    void inspectedFilesSelectionChanged(const QItemSelection& selection);

    void on_inspectedCopiesList_doubleClicked(const QModelIndex &index);

    void on_deleteDuplicatesBtn_clicked();

private:
    void init();
    void deleteFile(const QString &filename);
    void deleteFromDb(const int id);

    Ui::FindDuplicatesDialog *_ui;

    QSqlDatabase *_database;

    QStringListModel *_inspectedModel;
    QStringListModel *_inspectedCopiesModel;

    CDopelgangersLibrary *_library;

    QStringList _bookList, _dopelgangersList;
};

#endif // FINDDUPLICATESDIALOG_H
