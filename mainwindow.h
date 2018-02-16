#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QShortcut>

#include <QStringList>

#include <QCryptographicHash>
#include <QByteArray>
#include <QStyledItemDelegate>


namespace Ui {
class MainWindow;
}

class BackgroundColorDelegate;

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

    void on_colorDuplicatesBtn_clicked();

private:
    void initModel();
    void resizeTableView();
    void openDb();
    void saveDb();
    void saveAsDb();
    void createNewDb();
    void scanFolder();
    void processFolder(const QString path);
    void colorSameMd5();


    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);

    Ui::MainWindow *_ui;

    QSqlDatabase _database;
    QSqlTableModel *_databaseModel;

    QString _dbFilename;

    QShortcut *_deleteShortcut;

    QStringList _extensionList;

    BackgroundColorDelegate *_backgroundColorDelegate;
};

#endif // MAINWINDOW_H
