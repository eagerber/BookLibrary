#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingswindow.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

}

void MainWindow::on_actionAutomatic_process_triggered()
{

}

void MainWindow::onFilter()
{

}
