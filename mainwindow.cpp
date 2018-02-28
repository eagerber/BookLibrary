#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QtSql>

#include <QDirIterator>
#include <QStringList>
#include <QDesktopServices>
#include <QTableWidget>

#include "settingswindow.h"
#include "findduplicatesdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _database = QSqlDatabase::addDatabase("QSQLITE");
    _databaseModel = nullptr;

    _deleteShortcut = new QShortcut(QKeySequence(QKeySequence::Delete), _ui->tableView);
    connect(_deleteShortcut, SIGNAL(activated()), this, SLOT(deleteRow()));

    _ui->actionSave->setEnabled(false);
    _ui->actionSaveAs->setEnabled(false);
    _ui->scanDirectoryBtn->setEnabled(false);
    _ui->addRowBtn->setEnabled(false);

    _extensionList << "pdf" << "djvu" << "doc" << "docx" << "fb2";

    _ui->progressBar->show();
    _ui->progressBar->setValue(0);

    // TODO: make it static
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    _userProfileDesktop = QString(environment.value("userprofile") + "\\Desktop");
    _allUserProfileDesktop = QString(environment.value("allusersprofile") + "\\Desktop");
    _publicDesktop = QString(environment.value("public") + "\\Desktop");
}

void MainWindow::deleteRow()
{
    QItemSelectionModel *select = _ui->tableView->selectionModel();

    foreach (const auto &idx, select->selectedIndexes())
    {
        if (idx.isValid())
        {
           _ui->tableView->model()->removeRow(idx.row(), idx.parent());
        }
    }

    if( _databaseModel->submitAll() )
    {
        _databaseModel->database().commit();
        _databaseModel->select();
    }   
    else
    {
        _databaseModel->database().rollback();  
    }
}

MainWindow::~MainWindow()
{
    _database.close();
    delete _databaseModel;
    delete _ui;
}

void MainWindow::initModel()
{
    if(!_database.isOpen())
    {
        qDebug() << "No DB connection";
        return;
    }

    if(_databaseModel != nullptr)
    {
        delete _databaseModel;
    }

    _databaseModel = new QSqlTableModel(this, _database);

    _databaseModel->setTable("Catalog");
    _databaseModel->select();
    _databaseModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    _ui->tableView->setModel(_databaseModel);

    _ui->tableView->verticalHeader()->hide();
    _ui->tableView->horizontalHeader()->show();

    resizeTableView();
}

void MainWindow::resizeTableView()
{
    int size = _ui->tableView->width() - 10;
    _ui->tableView->setColumnWidth(0, size * 0.05);
    _ui->tableView->setColumnWidth(1, size * 0.5);
    _ui->tableView->setColumnWidth(2, size * 0.19);
    _ui->tableView->setColumnWidth(3, size * 0.05);
    _ui->tableView->setColumnWidth(4, size * 0.1);
    _ui->tableView->setColumnWidth(5, size * 0.1);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   // Your code here.

   resizeTableView();
}

void MainWindow::openDb()
{
    _dbFilename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));
    qDebug() << "Open File:" << _dbFilename;

    if(_dbFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

    if(_database.isOpen())
    {
        _database.close();
    }

    _database.setDatabaseName(_dbFilename);

    if (!_database.open())
    {
        return;
    }

    if(_databaseModel != 0)
    {
        delete _databaseModel;
    }

    _databaseModel = new QSqlTableModel(this, _database);

    initModel();

    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
}

void MainWindow::saveDb()
{
    if (!_database.open())
    {
        return;
    }

    _database.commit();
}

void MainWindow::saveAsDb()
{
    if (!_database.open())
    {
        qDebug() << "No Db for save.";
        return;
    }

    QString newFilename = QFileDialog::getSaveFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));
    if(newFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

    qDebug() << "Save File:" <<  newFilename;

    _database.close();

    QFile::remove(newFilename);
    QFile::copy(_dbFilename, newFilename);

    _dbFilename = newFilename;
    _database.setDatabaseName(_dbFilename);

    if (!_database.open())
    {
        return;
    }

    initModel();
}

void MainWindow::createNewDb()
{
    _dbFilename = QFileDialog::getSaveFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));

    if(_dbFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }
    qDebug() << "New DB File:" <<  _dbFilename;

    QFile::remove(_dbFilename);

    if(_database.isOpen())
    {
        _database.close();
    }

    _database.setDatabaseName(_dbFilename);

    if (!_database.open())
    {
        return;
    }

    _database.exec("CREATE TABLE `Catalog` ( `Id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `FullPath` TEXT, `Name` TEXT, `Extension` TEXT, `Size` INTEGER, `MD5`	BLOB);");
    _database.commit();

    initModel();

    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
}

void MainWindow::scanFolder()
{
    if(_dbFilename.isEmpty())
    {
        qDebug() << "No open database";
        return;
    }

    if (_extensionList.isEmpty())
    {
        qDebug() << "No extansions for scan";
        return;
    }

    QDir dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.exists())
    {
        qDebug() << "No folder for scan";
        return;
    }

    _ui->progressBar->show();
    _ui->progressBar->setValue(0);

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QDir userProfileDesktop = QString(environment.value("userprofile") + "\\Desktop");
    QDir allUserProfileDesktop = QString(environment.value("allusersprofile") + "\\Desktop");
    QDir publicDesktop = QString(environment.value("public") + "\\Desktop");

    QStringList maskList;
    foreach (const auto& item, _extensionList)
    {
        maskList << "*." + item;
    }


    QStringList dirsForScanning = getDirsForScanning(dir.path());
    int totalCount = filesCount(dirsForScanning, maskList);
    _ui->progressBar->setMaximum(totalCount);

    processFolders(dirsForScanning, maskList);

    _ui->progressBar->setValue(_ui->progressBar->maximum());
    _ui->progressBar->hide();
}

void MainWindow::stepProgress()
{
    QCoreApplication::processEvents();
    _ui->progressBar->setValue(_ui->progressBar->value() + 1);
}

int MainWindow::filesCount(const QStringList &dirs, const QStringList &maskList)
{
    int result = 0;

    foreach (const auto &dir, dirs)
    {
        QDirIterator it(dir, maskList, QDir::Files, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
        int count = 0;
        while (it.hasNext())
        {
            count++;
            qDebug() << it.next();
        }

        result += count;
    }

    return result;
}

QStringList MainWindow::getDirsForScanning(const QDir &dir)
{
    QStringList result;

    if(dir == _userProfileDesktop ||
       dir == _allUserProfileDesktop ||
       dir == _publicDesktop)
    {
        addToDirsForScanning(_userProfileDesktop.path(), result);
        addToDirsForScanning(_allUserProfileDesktop.path(), result);
        addToDirsForScanning(_publicDesktop.path(), result);
    }
    else
    {
        addToDirsForScanning(dir.path(), result);
    }


    QDirIterator it(dir.path(), QStringList() << "*.lnk", QDir::AllEntries, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();

        QFileInfo currentFileInfo = it.fileInfo();

        if(currentFileInfo.isSymLink())
        {
            QString symLinkTarget = currentFileInfo.symLinkTarget();
            result << getDirsForScanning(symLinkTarget);
        }
    }

    return result;
}

void MainWindow::addToDirsForScanning(const QString &path, QStringList &dirsForScanning)
{
    if(dirsForScanning.indexOf(path) == -1)
    {
        dirsForScanning << path;
    }
}

void MainWindow::processFolders(const QStringList &dirs, const QStringList &maskList)
{
    foreach (const auto &dir, dirs)
    {
        processFolder(dir, maskList);
    }
}

void MainWindow::processFolder(const QString &path, const QStringList &maskList)
{
    _database.transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO Catalog (FullPath, Name, Extension, Size, MD5) VALUES(:FullPath,:Name,:Extension,:Size, :MD5);");

    QDirIterator it(path, maskList, QDir::Files, QDirIterator::Subdirectories);
    int count = 0;
    while (it.hasNext())
    {
        count++;
        stepProgress();
        qDebug() << it.next();

        QString fullPath = it.filePath();
        QString fileName = it.fileName();
        QString extension = it.fileInfo().suffix().toLower();
        QString size = QString::number(it.fileInfo().size());
        QByteArray hash = fileChecksum(fullPath, QCryptographicHash::Algorithm::Md5);

        query.bindValue(":FullPath", fullPath);
        query.bindValue(":Name", fileName);
        query.bindValue(":Extension", extension);
        query.bindValue(":Size", size);
        query.bindValue(":MD5", hash);

        qDebug() << query.exec() << endl;
    }

    qDebug() << "Finish scan.";

    _database.commit();
    _databaseModel->select();
}

void MainWindow::on_actionOpen_triggered()
{
    openDb();
}

void MainWindow::on_addRowBtn_clicked()
{
    _database.exec("INSERT INTO Catalog DEFAULT VALUES;");
    _database.commit();

    _databaseModel->select();
}

void MainWindow::on_actionCreateNew_triggered()
{
    createNewDb();
}

void MainWindow::on_actionSave_triggered()
{
    saveDb();
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveAsDb();
}

void MainWindow::on_scanDirectoryBtn_clicked()
{
    scanFolder();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString path = _ui->tableView->model()->data(_ui->tableView->model()->index(index.row(), 1)).toString();
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsWindow *settings = new SettingsWindow(nullptr, _extensionList);

    settings->exec();

    delete settings;
}

QByteArray MainWindow::fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f))
        {
            return hash.result();
        }
    }

    return QByteArray();
}

void MainWindow::on_actionManual_process_triggered()
{
    FindDuplicatesDialog *settings = new FindDuplicatesDialog(nullptr, &_database);

    settings->exec();

    delete settings;

    _databaseModel->select();
}
