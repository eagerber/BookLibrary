#include "cbook.h"


CBook::CBook()
{

}

CBook::CBook(const CBook &rValue)
    : CBook()
{
    _id = rValue._id;
    _name = rValue._name;
    _fullPath = rValue._fullPath;
    _extension = rValue._extension;
    _size = rValue._size;
    _md5 = rValue._md5;
}

CBook::CBook(
        const int id,
        const QString &name,
        const QString &fullPath,
        const QString &extension,
        const int &size,
        const QByteArray &md5)
    : CBook()
{
    _id = id;
    _name = name;
    _fullPath = fullPath;
    _extension = extension;
    _size = size;
    _md5 = md5;
}

CBook::~CBook()
{

}

CBook& CBook::operator= (const CBook& rValue)
{
    _id = rValue._id;
    _name = rValue._name;
    _fullPath = rValue._fullPath;
    _extension = rValue._extension;
    _size = rValue._size;
    _md5 = rValue._md5;
    return *this;
}

bool CBook::operator== (const CBook& rValue) const
{
    return _id        == rValue._id &&
           _name      == rValue._name &&
           _fullPath  == rValue._fullPath &&
           _extension == rValue._extension &&
           _size      == rValue._size &&
           _md5       == rValue._md5;
}


bool CBook::fullMatch (const CBook& rValue) const
{
    return _name      == rValue._name &&
           _fullPath  == rValue._fullPath &&
           _extension == rValue._extension &&
           _size      == rValue._size &&
           _md5       == rValue._md5;
}

bool CBook::HashSumMatch(const CBook& rValue) const
{
    return _md5 == rValue._md5;
}

int CBook::id() const
{
    return _id;
}

QString CBook::name() const
{
    return _name;
}

QString CBook::fullPath() const
{
    return _fullPath;
}

QString CBook::extension() const
{
    return _extension;
}

int CBook::size() const
{
    return _size;
}

QByteArray CBook::md5() const
{
    return _md5;
}
