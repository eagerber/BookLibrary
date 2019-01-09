#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingswindow.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _adapter = new CDatabaseAdapter();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _adapter;
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_addRowBtn_clicked()
{

}

void MainWindow::deleteRow()
{

}

void MainWindow::on_actionCreateNew_triggered()
{
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actionSaveAs_triggered()
{
}

void MainWindow::on_scanDirectoryBtn_clicked()
{
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
    _ui->menuDuplicates->setEnabled(true);
}
