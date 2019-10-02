#include "replacebyextensiondialog.h"
#include "ui_replacebyextensiondialog.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>


#include "clibrary.h"
#include "cbook.h"



ReplaceByExtensionDialog::ReplaceByExtensionDialog(CLibrary &library, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceByExtensionDialog),
    _library(library)
{
    ui->setupUi(this);


    initModel();
}

ReplaceByExtensionDialog::~ReplaceByExtensionDialog()
{
    delete ui;
}


void ReplaceByExtensionDialog::on_replacePushButton_clicked()
{
    QString path = ui->destinationFolderLineEdit->text();

    if(path.isNull()) return;
    if(path.isEmpty()) return;

    auto data = _library.data();
    foreach(auto item, _replacement)
    {
        _library.replaceBook(*data[item.first], item.second);
    }

    QMessageBox::information(this, "Information", "Files were replaced. Check destination folder.", QMessageBox::Ok);
}

void ReplaceByExtensionDialog::initModel()
{
    _replacement.clear();
    QDir path(ui->destinationFolderLineEdit->text());
    QStringList availableExtensions = _library.availableExtensions();

    auto data = _library.data();
    if(availableExtensions.length() > 0)
    {
        _model = new QStandardItemModel(data.length() + availableExtensions.length(), 1);

        for(int i = 0; i < availableExtensions.length(); ++i)
        {
            QString currentExtension = availableExtensions[i];
            QStandardItem *item = new QStandardItem(currentExtension);

            for(int j = 0; j < data.length(); ++j)
            {
                auto book = data[j];
                if(book->extension() != currentExtension) continue;

                QString newBookFilePath = path.filePath(currentExtension + QDir::separator() + book->name());
                QStandardItem *child = new QStandardItem(newBookFilePath);
                child->setEditable(false);
                item->appendRow(child);

                _replacement.append(qMakePair(j, newBookFilePath));
            }
            _model->setItem(i, 0, item);
        }
        ui->previewTreeView->setModel(_model);
        ui->previewTreeView->header()->hide();
        ui->previewTreeView->expandAll();
    }
}

void ReplaceByExtensionDialog::on_destinationFolderToolButton_clicked()
{
    QDir dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.exists())
    {
        qDebug() << "No folder for scan";
        return;
    }

    ui->destinationFolderLineEdit->setText(dir.path());

    ui->destinationFolderLineEdit->editingFinished();
}


void ReplaceByExtensionDialog::on_destinationFolderLineEdit_returnPressed()
{
    initModel();
}

void ReplaceByExtensionDialog::on_ReplaceByExtensionDialog_accepted()
{
    return;
}
