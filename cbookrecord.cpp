#include "cbookrecord.h"

CBookRecord::CBookRecord()
    : QObject()
{

}

CBookRecord::CBookRecord(const CBookRecord &rValue)
    : CBookRecord()
{
    _id = rValue._id;
    _name = rValue._name;
    _fullPath = rValue._fullPath;
}

CBookRecord::CBookRecord(const int id, const QString &name, const QString &fullPath)
    : CBookRecord()
{
    _id = id;
    _name = name;
    _fullPath = fullPath;
}

CBookRecord::~CBookRecord()
{

}

int CBookRecord::id() const
{
    return _id;
}

QString CBookRecord::name() const
{
    return _name;
}

QString CBookRecord::fullPath() const
{
    return _fullPath;
}
