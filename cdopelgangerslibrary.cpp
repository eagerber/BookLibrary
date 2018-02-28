#include "cdopelgangerslibrary.h"

#include <QSqlQuery>
#include <QDebug>

// WinAPI move to recycle bin
#include "Windows.h"
#include "shellapi.h"

CDopelgangersLibrary::CDopelgangersLibrary()
    : QObject()
{
}

CDopelgangersLibrary::CDopelgangersLibrary(const CDopelgangersLibrary &rValue)
    : CDopelgangersLibrary()
{
    _booksList = rValue._booksList;
}

CDopelgangersLibrary::~CDopelgangersLibrary()
{

}

void CDopelgangersLibrary::init()
{
    QSqlQuery query;
    query.exec("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog c2 WHERE ( SELECT COUNT(*) FROM Catalog c1 WHERE c1.MD5 = c2.MD5 ) > 1 ORDER BY MD5;");

    QByteArray prevMd5;
    int prevSize = -1;
    int currentItem = -1;
    while (query.next())
    {
        QByteArray currentMd5 = query.value(5).toByteArray();
        int currentSize = query.value(4).toInt();

        QString name = query.value(2).toString();
        QString fullPath = query.value(1).toString();
        int id = query.value(0).toInt();

        if ((prevMd5 != currentMd5) || (prevSize != currentSize))
        {
            currentItem++;

            addItem(CBookList(id, name, fullPath));
        }
        last().addDuplicate(CBook(id, name, fullPath));

        prevMd5 = currentMd5;
        prevSize = currentSize;
    }

    query.clear();
}

void CDopelgangersLibrary::addItem(const CBookList &bookRecord)
{
    _booksList.push_back(bookRecord);
}


CBookList& CDopelgangersLibrary::last()
{
    return _booksList.last();
}

CBookList& CDopelgangersLibrary::first()
{
    return _booksList.first();
}

CBookList& CDopelgangersLibrary::at(const int index)
{
    return _booksList[index];
}

CBook& CDopelgangersLibrary::at(const int booksListIndex, const int bookIndex)
{
    return _booksList[booksListIndex].at(bookIndex);
}

int CDopelgangersLibrary::length()
{
    return _booksList.length();
}

QStringList CDopelgangersLibrary::books()
{
    QStringList result;

    foreach (const auto &book, _booksList)
    {
        result << book.name();
    }

    return result;
}

QStringList CDopelgangersLibrary::duplicatesByIndex(const int index)
{
    if(_booksList.length() > 0)
    {
        return _booksList[index].toStringList();
    }

    return QStringList();
}

void CDopelgangersLibrary::normalize(const int booksListIndex, const int trueBookIndex)
{
    auto &currentBookList = at(booksListIndex);
    auto trueBookFullPath = currentBookList.at(trueBookIndex).fullPath();

    for(int i = currentBookList.length() - 1; i > -1; --i)
    {
        if(i == trueBookIndex)
        {
            continue;
        }

        CBook currentBook = currentBookList.at(i);

        deleteFromDb(currentBook.id());

        auto currentFullPath = currentBook.fullPath();
        if(currentFullPath != trueBookFullPath)
        {
            deleteFile(currentFullPath);
        }
    }
}

void CDopelgangersLibrary::normalize()
{
    for(int i = 0; i < _booksList.length(); ++i)
    {
        normalize(i);
    }
}

void CDopelgangersLibrary::deleteFile(const QString &filename)
{
    //QFile file(filename);
    //file.remove();

    // Move to recycle bin
    LPCSTR lpcFrom = (LPCSTR)filename.toLocal8Bit().constData();

    SHFILEOPSTRUCTA operation;

    operation.wFunc = FO_DELETE;
    operation.pFrom = lpcFrom;
    operation.fFlags = FOF_ALLOWUNDO|FOF_NO_UI|FOF_NORECURSION;

    int result = SHFileOperationA(&operation);

    qDebug() << filename << result;
}

void CDopelgangersLibrary::deleteFromDb(const int id)
{
    //QString query = QString("DELETE FROM Catalog WHERE Id = %1").arg(id);

    QSqlQuery query;
    query.exec(QString("DELETE FROM Catalog WHERE Id = %1;").arg(id));

    query.clear();
    //_database->exec(query);
    //_database->commit();
}

