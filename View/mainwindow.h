#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCryptographicHash>
#include <QByteArray>
#include <QSharedPointer>
#include <QStandardItemModel>

#include "cdatabaseadapter.h"

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

    void onFilter();

private:
    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);
    void openDb(QString filename);
    void saveAsDb();
    void initModel();
    void loadDataToModel();
    void resizeTableView();
    void createNewDb();
    void scanFolder();
    void processFolder(const QString path);

    Ui::MainWindow *_ui;

    QSharedPointer<CDatabaseAdapter> _adapter;
    QString _dbFilename;
    QStringList _extensionList;
    QList<CBook> _data;
    QStandardItemModel _model;
};

#endif // MAINWINDOW_H
