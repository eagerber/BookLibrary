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
}

CBook::CBook(const int id, const QString &name, const QString &fullPath)
    : CBook()
{
    _id = id;
    _name = name;
    _fullPath = fullPath;
}

CBook::~CBook()
{

}

CBook& CBook::operator= (const CBook& rValue)
{
    _id = rValue._id;
    _name = rValue._name;
    _fullPath = rValue._fullPath;
    return *this;
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
