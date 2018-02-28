#include "cduplicatedbookrecord.h"


CDuplicatedBookRecord::CDuplicatedBookRecord()
    : CBookRecord()
{

}

CDuplicatedBookRecord::CDuplicatedBookRecord(const CDuplicatedBookRecord &rValue)
    : CBookRecord(rValue)
{
    _dopelgangers = rValue._dopelgangers;
}

CDuplicatedBookRecord::CDuplicatedBookRecord(const int id, const QString &name, const QString &fullPath)
    : CBookRecord(id, name, fullPath)
{

}

void CDuplicatedBookRecord::addDuplicate(const CBookRecord &duplicate)
{
    _dopelgangers.push_back(duplicate);
}

CBookRecord& CDuplicatedBookRecord::at(const int index)
{
    return _dopelgangers[index];
}

QStringList CDuplicatedBookRecord::dopelgangersStringList()
{
    QStringList result;

    foreach (const auto &dopelganger, _dopelgangers)
    {
        result << dopelganger.fullPath();
    }

    return result;
}

