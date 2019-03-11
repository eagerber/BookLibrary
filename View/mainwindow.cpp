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


#include "cbook.h"
#include "findduplicatesdialog.h"
#include "automaticduplicatesprocessdialog.h"


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

    _adapter = nullptr;
    _data.clear();

    openDb("123.sqlite");
}

MainWindow::~MainWindow()
{
    delete _deleteShortcut;
    delete _ui;
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
    qDebug() << "Open File:" << _dbFilename;

    if(_dbFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

    openDb(filename);
}

void MainWindow::on_addRowBtn_clicked()
{
    _data.insert(0, CBook());

    loadDataToModel();
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
    _adapter->saveChanges(_data);
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
    FindDuplicatesDialog findDuplicatesDialog;
    findDuplicatesDialog.exec();

    //_databaseModel->select();
}

void MainWindow::on_actionAutomatic_process_triggered()
{
    AutomaticDuplicatesProcessDialog automaticDuplicatesProcessDialog;
    automaticDuplicatesProcessDialog.exec();

    //CDopelgangersLibrary library;
    //
    //library.init();
    //library.normalize();

    //_databaseModel->select();
}

void MainWindow::onFilter()
{
    QString fullPathFilter = _ui->fullPathFilterLineEdit->text();
    QString nameFilter = _ui->nameFilterLineEdit->text();
    QString extensionFilter = _ui->extensionFilterLineEdit->text();

    if(fullPathFilter.isEmpty() && nameFilter.isEmpty() && extensionFilter.isEmpty())
    {
        _model.setFilter("");
        return;
    }

    QString filter = "";

    QString filterTemplate = QString("%1 LIKE '\%%2\%'");
    QString andFilterTemplate = QString(" AND %1 LIKE '\%%2\%'");
    if(!fullPathFilter.isEmpty())
    {
        filter = filterTemplate.arg("FullPath").arg(fullPathFilter);

        filterTemplate = andFilterTemplate;
    }
    if(!nameFilter.isEmpty())
    {
        filter = filter + filterTemplate.arg("Name").arg(nameFilter);

        filterTemplate = andFilterTemplate;
    }
    if(!extensionFilter.isEmpty())
    {
        filter = filter + filterTemplate.arg("Extension").arg(extensionFilter);
    }

    _model.setFilter(filter);
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

    _dbFilename = filename;
    _adapter = QSharedPointer<CDatabaseAdapter>(new CDatabaseAdapter(_dbFilename));

    initModel();

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
    QFile::copy(_dbFilename, newFilename);

    _dbFilename = newFilename;

    _adapter = QSharedPointer<CDatabaseAdapter>(new CDatabaseAdapter(_dbFilename));

    initModel();

    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
    _ui->menuDuplicates->setEnabled(true);
}

void MainWindow::initModel()
{
   _data = _adapter->readAll();

   loadDataToModel();
   resizeTableView();
}

void MainWindow::loadDataToModel()
{
    _model.clear();

    QStringList horizontalHeader;
    horizontalHeader.append("id");
    horizontalHeader.append("name");
    horizontalHeader.append("fullPath");
    horizontalHeader.append("extension");
    horizontalHeader.append("size");
    horizontalHeader.append("md5");
    _model.setHorizontalHeaderLabels(horizontalHeader);

    for(int i = 0; i < _data.length(); ++i)
    {
        _model.setItem(i, 0, new QStandardItem(QString::number(_data[i].id())));
        _model.setItem(i, 1, new QStandardItem(_data[i].name()));
        _model.setItem(i, 2, new QStandardItem(_data[i].fullPath()));
        _model.setItem(i, 3, new QStandardItem(_data[i].extension()));
        _model.setItem(i, 4, new QStandardItem(QString::number(_data[i].size())));
        _model.setItem(i, 5, new QStandardItem(QString(_data[i].md5())));
    }

    _ui->tableView->setModel(&_model);
}


void MainWindow::resizeTableView()
{
    _ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    _ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    /*
    int size = _ui->tableView->width() - 10;
    _ui->tableView->setColumnWidth(0, static_cast<int>(size * 0.05));
    _ui->tableView->setColumnWidth(1, static_cast<int>(size * 0.5));
    _ui->tableView->setColumnWidth(2, static_cast<int>(size * 0.19));
    _ui->tableView->setColumnWidth(3, static_cast<int>(size * 0.05));
    _ui->tableView->setColumnWidth(4, static_cast<int>(size * 0.1));
    _ui->tableView->setColumnWidth(5, static_cast<int>(size * 0.1));
    */
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

    _dbFilename = currentFilename;
    QFile::remove(_dbFilename);

    _adapter =  QSharedPointer<CDatabaseAdapter>(new CDatabaseAdapter(_dbFilename));

    initModel();

    // TODO: move to method
    _ui->actionSave->setEnabled(true);
    _ui->actionSaveAs->setEnabled(true);
    _ui->scanDirectoryBtn->setEnabled(true);
    _ui->addRowBtn->setEnabled(true);
    _ui->menuDuplicates->setEnabled(true);
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

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QDir userProfileDesktop = QString(environment.value("userprofile") + "\\Desktop");
    QDir allUserProfileDesktop = QString(environment.value("allusersprofile") + "\\Desktop");
    QDir publicDesktop = QString(environment.value("public") + "\\Desktop");

    if(dir == userProfileDesktop ||
       dir == allUserProfileDesktop ||
       dir == publicDesktop)
    {
        processFolder(userProfileDesktop.path());
        processFolder(allUserProfileDesktop.path());
        processFolder(publicDesktop.path());
    }
    else
    {
        processFolder(dir.path());
    }
    _adapter->saveChanges(_data);
    loadDataToModel();
}


void MainWindow::processFolder(const QString path)
{
    QStringList maskList;
    foreach (const auto& item, _extensionList)
    {
        maskList << "*." + item;
    }

    int id = 0;
    foreach(auto& item, _data)
    {
        id = std::max(id, item.id());
    }

    QDirIterator it(path, maskList, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();

        QString fullPath = it.filePath();
        QString fileName = it.fileName();
        QString extension = it.fileInfo().suffix().toLower();
        auto size = it.fileInfo().size();
        QByteArray hash = fileChecksum(fullPath, QCryptographicHash::Algorithm::Md5);

        _data.append(CBook(++id, fileName, fullPath, extension, size, hash));
    }

    qDebug() << "Finish scan.";

}









