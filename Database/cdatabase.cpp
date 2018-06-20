#include "cdatabase.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFileInfo>
#include <QException>
#include <QDebug>
#include <QDir>


const QString createQuery = "CREATE TABLE `Catalog` ( `Id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `FullPath` TEXT, `Name` TEXT, `Extension` TEXT, `Size` INTEGER, `MD5`	BLOB);";

class CDatabasePimpl
{
public:
    CDatabasePimpl()
    {
        _database = QSqlDatabase::addDatabase("QSQLITE");
    }

    ~CDatabasePimpl()
    {
        close();
    }

    QSqlDatabase& database()
    {
        return _database;
    }

    void openDatabase(QString filename)
    {
        QFileInfo fileInfo(filename);
        qDebug() << fileInfo.absolutePath();

        QDir dir(fileInfo.absolutePath());
        if(filename.isEmpty() || !dir.exists())
        {
            throw QException();
        }

        if(filename == _filename)
        {
            return;
        }

        close();

        _filename = filename;

        internalOpen();
    }

    void close()
    {
        if(_database.isOpen())
        {
            _database.close();
        }
    }

private:

    bool open()
    {
        _database.setDatabaseName(_filename);
        return _database.open();
    }

    void internalOpen()
    {
        bool fileNotExists = !QFile::exists(_filename);
        if (!open())
        {
            qDebug() << _database.lastError().text();
            throw QException();
        }

        if(fileNotExists)
        {
            createNewDatabase();
        }
    }

    void createNewDatabase()
    {
        _database.exec(createQuery);
        _database.commit();
    }

    void checkMigration()
    {

    }

    void migrateUp()
    {

    }

    void migrateDown()
    {

    }

    QSqlDatabase _database;
    QString _filename;

};


CDatabase::CDatabase()
{
    _pimpl = new CDatabasePimpl();
}

CDatabase::~CDatabase()
{
    delete _pimpl;
}

QSqlDatabase& CDatabase::instance()
{
    return _pimpl->database();
}

void CDatabase::open(const QString filename)
{
    _pimpl->openDatabase(filename);
}

void CDatabase::close()
{
    _pimpl->close();
}

