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


#include "cbook.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->actionSave->setEnabled(false);
    _ui->actionSaveAs->setEnabled(false);
    _ui->scanDirectoryBtn->setEnabled(false);
    _ui->addRowBtn->setEnabled(false);

    _extensionList << "pdf" << "djvu" << "doc" << "docx" << "fb2";

    _adapter = nullptr;
    _data.clear();
}

MainWindow::~MainWindow()
{
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
    openDb();
}

void MainWindow::on_addRowBtn_clicked()
{
    _data.insert(0, CBook());

    loadDataToModel();
}

void MainWindow::deleteRow()
{

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
}

void MainWindow::on_actionSettings_triggered()
{
}

void MainWindow::on_actionManual_process_triggered()
{

}

void MainWindow::on_actionAutomatic_process_triggered()
{

}

void MainWindow::onFilter()
{

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

void MainWindow::openDb()
{
    _dbFilename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".\\", tr("Image Files (*.sqlite)"));
    qDebug() << "Open File:" << _dbFilename;

    if(_dbFilename.isEmpty())
    {
        qDebug() << "Empty filename.";
        return;
    }

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
    auto model = QSharedPointer<QStandardItemModel>(new QStandardItemModel());

    QStringList horizontalHeader;
    horizontalHeader.append("id");
    horizontalHeader.append("name");
    horizontalHeader.append("fullPath");
    horizontalHeader.append("extension");
    horizontalHeader.append("size");
    horizontalHeader.append("md5");
    model->setHorizontalHeaderLabels(horizontalHeader);

    for(int i = 0; i < _data.length(); ++i)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(_data[i].id())));
        model->setItem(i, 1, new QStandardItem(_data[i].name()));
        model->setItem(i, 2, new QStandardItem(_data[i].fullPath()));
        model->setItem(i, 3, new QStandardItem(_data[i].extension()));
        model->setItem(i, 4, new QStandardItem(QString::number(_data[i].size())));
        model->setItem(i, 5, new QStandardItem(QString(_data[i].md5())));
    }

    _ui->tableView->setModel(model.data());
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

    QDirIterator it(path, maskList, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();

        int id = 0;
        QString fullPath = it.filePath();
        QString fileName = it.fileName();
        QString extension = it.fileInfo().suffix().toLower();
        auto size = it.fileInfo().size();
        QByteArray hash = fileChecksum(fullPath, QCryptographicHash::Algorithm::Md5);

        _data.append(CBook(id, fileName, fullPath, extension, size, hash));
    }

    qDebug() << "Finish scan.";

}









