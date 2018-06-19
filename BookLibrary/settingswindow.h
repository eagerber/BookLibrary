#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

#include <QShortcut>
#include <QStringList>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    SettingsWindow(QWidget *parent, QStringList &extensionList);
    ~SettingsWindow();

private slots:
    void on_addExtensionBtn_clicked();
    void deleteRow();

private:
    Ui::SettingsWindow *_ui;

    QShortcut *_deleteShortcut;
    QStringList *_extensionList;
};

#endif // SETTINGSWINDOW_H
