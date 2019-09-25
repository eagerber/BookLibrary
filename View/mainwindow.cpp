#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingswindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDirIterator>
#include <QDesktopServices>
#include <QModelIndex>

#include "findduplicatesdialog.h"
#include "automaticduplicatesprocessdialog.h"
#include "booklibrarymodel.h"
#include "proxybooklibrarymodel.h"
#include "cbook.h"
#include "clibrary.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _deleteShortcut = new QShortcut(QKeySequence(QKeySequence::Delete), _ui->tableView);
    connect(_deleteShortcut, SIGNAL(activated()), this, SLOT(deleteRow()));

    _ui->actionSave->setEnabled(false);
    _ui->actionSaveAs->setEnabled(false);
    _ui->scanDirectoryBtn->setEnabled(false);
    _ui->addRowBtn->setEnabled(false);

    _extensionList << "pdf" << "djvu" << "doc" << "docx" << "fb2";

    _ui->progressBar->show();
    _ui->progressBar->setValue(0);

    openDb("123.sqlite");
}

MainWindow::~MainWindow()
{
    delete _deleteShortcut;
    delete _ui;
}

void MainWindow::updateData(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    QModelIndex valueIndex(topLeft);

    _ui->tableView->model()->setData(
                topLeft, _ui->tableView->model()->data(topLeft));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   // Your code here.

   resizeTableView();
}

void MainWindow::on_actionOpen_triggered()
{    
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));
    qDebug() << "Open File:" << filename;

    if(filename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

    openDb(filename);
}

void MainWindow::on_addRowBtn_clicked()
{
    _model->add(CBook());
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
}

void MainWindow::on_actionCreateNew_triggered()
{
    createNewDb();
}

void MainWindow::on_actionSave_triggered()
{
    _model->saveChanges();
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

void MainWindow::on_actionManual_process_triggered()
{
    FindDuplicatesDialog findDuplicatesDialog(_model->library());
    findDuplicatesDialog.exec();

    //_databaseModel->select();
}

void MainWindow::on_actionAutomatic_process_triggered()
{
    AutomaticDuplicatesProcessDialog automaticDuplicatesProcessDialog(_model->library());
    automaticDuplicatesProcessDialog.exec();

    //CDopelgangersLibrary library;
    //
    //library.init();
    //library.normalize();

    //_databaseModel->select();
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

void MainWindow::openDb(QString filename)
{
    if(filename.isEmpty())
    {
        return;
    }

    initModel(filename);

    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
    _ui->menuDuplicates->setEnabled(true);
}

void MainWindow::saveAsDb()
{
    QString newFilename = QFileDialog::getSaveFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));
    if(newFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

    qDebug() << "Save File:" <<  newFilename;

    QFile::remove(newFilename);
    QFile::copy(_model->filename(), newFilename);

    initModel(newFilename);

    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
    _ui->menuDuplicates->setEnabled(true);
}

void MainWindow::resizeTableView()
{
    // TODO: use first column width
    int size = _ui->tableView->width();
    _ui->tableView->setColumnWidth(0, static_cast<int>(size * 0.4));
    _ui->tableView->setColumnWidth(1, static_cast<int>(size * 0.3));
    _ui->tableView->setColumnWidth(2, static_cast<int>(size * 0.08));
    _ui->tableView->setColumnWidth(3, static_cast<int>(size * 0.08));
}


void MainWindow::createNewDb()
{
    auto currentFilename = QFileDialog::getSaveFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));

    if(currentFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }
    qDebug() << "New DB File:" <<  currentFilename;

    QFile::remove(currentFilename);
    initModel(currentFilename);

    // TODO: move to method
    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
    _ui->menuDuplicates->setEnabled(true);
}

void MainWindow::scanFolder()
{
    if(!_model)
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

    QStringList maskList;
    foreach (const auto& item, _extensionList)
    {
        maskList << "*." + item;
    }

    QStringList dirsForScanning = getDirsForScanning(dir.path());
    int totalCount = filesCount(dirsForScanning, maskList);
    _ui->progressBar->setMaximum(totalCount);

    processFolders(dirsForScanning, maskList);

    //TODO: progress bar for delete duplicates
    deleteDuplicates();

    _model->saveChanges();

    updateTableView();

    _ui->progressBar->setValue(_ui->progressBar->maximum());
    _ui->progressBar->hide();
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

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QDir userProfileDesktop = QString(environment.value("userprofile") + "\\Desktop");
    QDir allUserProfileDesktop = QString(environment.value("allusersprofile") + "\\Desktop");
    QDir publicDesktop = QString(environment.value("public") + "\\Desktop");

    if(dir == userProfileDesktop ||
       dir == allUserProfileDesktop ||
       dir == publicDesktop)
    {
        addToDirsForScanning(userProfileDesktop.path(), result);
        addToDirsForScanning(allUserProfileDesktop.path(), result);
        addToDirsForScanning(publicDesktop.path(), result);
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

void MainWindow::initModel(QString filename)
{
    _model = QSharedPointer<BookLibraryModel>(new BookLibraryModel(filename));
    _model->init();

    updateTableView();
    //connect(_ui->tableView->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(updateData(QModelIndex,QModelIndex)));
}

// TODO: do something with it
void MainWindow::updateTableView()
{
    _proxyModel = QSharedPointer<ProxyBookLibraryModel>(new ProxyBookLibraryModel(_model.get()));
    _ui->tableView->setModel(_proxyModel.get());
}

void MainWindow::deleteDuplicates()
{
    _model->library().deleteDuplicates();
    updateTableView();
}

void MainWindow::processFolder(const QString path, const QStringList &maskList)
{
    int id = _model->maxIndex();

    QDirIterator it(path, maskList, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();
        stepProgress();

        QString fullPath = it.filePath();
        QString fileName = it.fileName();
        QString extension = it.fileInfo().suffix().toLower();
        auto size = it.fileInfo().size();
        QByteArray hash = fileChecksum(fullPath, QCryptographicHash::Algorithm::Md5);

        _model->add(CBook(++id, fileName, fullPath, extension, size, hash));
    }

    qDebug() << "Finish scan.";    
}


void MainWindow::stepProgress()
{
    QCoreApplication::processEvents();
    _ui->progressBar->setValue(_ui->progressBar->value() + 1);
}

void MainWindow::on_fullPathFilterLineEdit_editingFinished()
{
    _proxyModel->setFullPath(_ui->fullPathFilterLineEdit->text());
}

void MainWindow::on_nameFilterLineEdit_editingFinished()
{
    _proxyModel->setName(_ui->nameFilterLineEdit->text());
}

void MainWindow::on_extensionFilterLineEdit_editingFinished()
{
    _proxyModel->setExtension(_ui->extensionFilterLineEdit->text());
}

void MainWindow::on_actionRemove_full_copies_triggered()
{
    deleteDuplicates();
}
