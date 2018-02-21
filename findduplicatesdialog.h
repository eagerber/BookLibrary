#ifndef FINDDUPLICATESDIALOG_H
#define FINDDUPLICATESDIALOG_H

#include <QDialog>

#include <QSqlDatabase>
#include <QStringListModel>
#include <QItemSelection>

namespace Ui {
class FindDuplicatesDialog;
}

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

private:
    Ui::FindDuplicatesDialog *_ui;

    QSqlDatabase *_database;

    QStringListModel *_inspectedModel;
    QStringListModel *_inspectedCopiesModel;

    QVector<QStringList> inspectedCopiesData;
};

#endif // FINDDUPLICATESDIALOG_H
