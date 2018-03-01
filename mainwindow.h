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
#include <QDir>


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

private:
    void initModel();
    void resizeTableView();
    void openDb();
    void saveDb();
    void saveAsDb();
    void createNewDb();
    void scanFolder();
    void removeIdenticalRows();
    void processFolders(const QStringList &dirs, const QStringList &maskList);
    void processFolder(const QString &path, const QStringList &maskList);

    void stepProgress();

    QStringList getDirsForScanning(const QDir &dir);
    void addToDirsForScanning(const QString &path, QStringList &dirsForScanning);
    int filesCount(const QStringList &dirs, const QStringList &maskList);

    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);

    Ui::MainWindow *_ui;

    QSqlDatabase _database;
    QSqlTableModel *_databaseModel;

    QString _dbFilename;

    QShortcut *_deleteShortcut;

    QStringList _extensionList;

    QDir _userProfileDesktop;
    QDir _allUserProfileDesktop;
    QDir _publicDesktop;
};

#endif // MAINWINDOW_H
