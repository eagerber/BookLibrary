#include "findduplicatesdialog.h"
#include "ui_findduplicatesdialog.h"

#include <QSqlQuery>
#include <QStringList>

FindDuplicatesDialog::FindDuplicatesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDuplicatesDialog)
{
    ui->setupUi(this);
}

FindDuplicatesDialog::FindDuplicatesDialog(QWidget *parent, QSqlDatabase *database) :
    FindDuplicatesDialog(parent)
{
    _database = database;

    QSqlQuery query;
    query.exec("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog c2 WHERE ( SELECT COUNT(*) FROM Catalog c1 WHERE c1.MD5 = c2.MD5 ) > 1 ORDER BY MD5 ");

    _inspectedModel = new QStringListModel();
    _inspectedCopiesModel = new QStringListModel();

    QStringList inspectedData;

    QByteArray prevMd5;
    int currentItem = -1;
    while (query.next())
    {
        QByteArray currentMd5 = query.value(5).toByteArray();

        QString name = query.value(2).toString();
        QString fullPath = query.value(1).toString();

        if (prevMd5 != currentMd5)
        {
            currentItem++;
            inspectedCopiesData.push_back(QStringList());

            inspectedData << name;
        }
        inspectedCopiesData[currentItem] << fullPath;

        prevMd5 = currentMd5;
    }

    query.clear();

    _inspectedModel->setStringList(inspectedData);
    ui->inspectedFiles->setModel(_inspectedModel);

    _inspectedCopiesModel->setStringList(inspectedCopiesData[0]);
    ui->inspectedCopiesList->setModel(_inspectedCopiesModel);
}

FindDuplicatesDialog::~FindDuplicatesDialog()
{
    _database = nullptr;
    delete _inspectedModel;
    delete _inspectedCopiesModel;
    delete ui;
}

void FindDuplicatesDialog::on_inspectedFiles_clicked(const QModelIndex &index)
{
    delete _inspectedCopiesModel;
    _inspectedCopiesModel = new QStringListModel();

    int row = index.row();
    _inspectedCopiesModel->setStringList(inspectedCopiesData[row]);
    ui->inspectedCopiesList->setModel(_inspectedCopiesModel);
}

void FindDuplicatesDialog::on_inspectedFiles_pressed(const QModelIndex &index)
{
    delete _inspectedCopiesModel;
    _inspectedCopiesModel = new QStringListModel();

    int row = index.row();
    _inspectedCopiesModel->setStringList(inspectedCopiesData[row]);
    ui->inspectedCopiesList->setModel(_inspectedCopiesModel);
}
