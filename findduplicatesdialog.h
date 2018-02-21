#ifndef FINDDUPLICATESDIALOG_H
#define FINDDUPLICATESDIALOG_H

#include <QDialog>

#include <QSqlDatabase>
#include <QStringListModel>

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
    void on_inspectedFiles_clicked(const QModelIndex &index);

    void on_inspectedFiles_pressed(const QModelIndex &index);

private:
    Ui::FindDuplicatesDialog *ui;

    QSqlDatabase *_database;

    QStringListModel *_inspectedModel;
    QStringListModel *_inspectedCopiesModel;

    QVector<QStringList> inspectedCopiesData;
};

#endif // FINDDUPLICATESDIALOG_H
