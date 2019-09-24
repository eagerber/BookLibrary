#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCryptographicHash>
#include <QByteArray>
#include <QSharedPointer>
#include <QStandardItemModel>
#include <QShortcut>
#include <QSortFilterProxyModel>


#include "cdatabaseadapter.h"

class ProxyBookLibraryModel;
class BookLibraryModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent* event);

private slots:
    void on_actionOpen_triggered();

    void on_actionCreateNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_addRowBtn_clicked();

    void deleteRow();

    void on_scanDirectoryBtn_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionSettings_triggered();

    void on_actionManual_process_triggered();

    void on_actionAutomatic_process_triggered();

    void on_fullPathFilterLineEdit_editingFinished();

    void on_nameFilterLineEdit_editingFinished();

    void on_extensionFilterLineEdit_editingFinished();

    void updateData(const QModelIndex & indexA, const QModelIndex & indexB);

    void on_actionRemove_full_copies_triggered();

private:
    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);
    void openDb(QString filename);
    void saveAsDb();
    void resizeTableView();
    void createNewDb();
    void scanFolder();
    void processFolder(const QString path);
    void initModel(QString filename = "");
    void updateTableView();
    void deleteDuplicates();

    Ui::MainWindow *_ui;    
    QShortcut *_deleteShortcut;

    QStringList _extensionList;
    QSharedPointer<BookLibraryModel> _model;
    QSharedPointer<ProxyBookLibraryModel> _proxyModel;
};

#endif // MAINWINDOW_H
