#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QDebug>


SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::SettingsWindow),
    _extensionList(nullptr)
{
    _ui->setupUi(this);

    _deleteShortcut = new QShortcut(QKeySequence(QKeySequence::Delete), _ui->extensionListWidget);
    connect(_deleteShortcut, SIGNAL(activated()), this, SLOT(deleteRow()));
}

SettingsWindow::SettingsWindow(QWidget *parent, QStringList &extensionList) :
    SettingsWindow(parent)
{
    _extensionList = &extensionList;
    _ui->extensionListWidget->addItems(*_extensionList);
}

SettingsWindow::~SettingsWindow()
{
    _extensionList = nullptr;
    delete _ui;
}

void SettingsWindow::on_addExtensionBtn_clicked()
{
    QString extension = _ui->extensionEdit->text().toLower();
    if(extension.isEmpty())
    {
        return;
    }

    auto& list = _ui->extensionListWidget;
    for(int i = 0; i < list->count(); ++i)
    {
        if(extension == list->item(i)->text())
        {
            return;
        }
    }

    _ui->extensionListWidget->addItem(extension);
    _extensionList->append(extension);
}

void SettingsWindow::deleteRow()
{
    QItemSelectionModel *select = _ui->extensionListWidget->selectionModel();

    foreach (const auto &idx, select->selectedIndexes())
    {
        if (idx.isValid())
        {
            _ui->extensionListWidget->model()->removeRow(idx.row(), idx.parent());

            _extensionList->removeAt(idx.row());
        }
    }
}
