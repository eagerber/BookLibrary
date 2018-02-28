#ifndef CDUPLICATEDBOOKRECORD_H
#define CDUPLICATEDBOOKRECORD_H

#include <QOBject>
#include <QList>

#include "cbookrecord.h"

class CDuplicatedBookRecord : public CBookRecord
{
    Q_OBJECT

public:
    explicit CDuplicatedBookRecord();
    CDuplicatedBookRecord(const CDuplicatedBookRecord &rValue);

    CDuplicatedBookRecord(const int id, const QString &name, const QString &fullPath);

    void addDuplicate(const CBookRecord &duplicate);
    CBookRecord& at(const int index);

    QStringList dopelgangersStringList();

private:
    QList<CBookRecord> _dopelgangers;
};

#endif // CDUPLICATEDBOOKRECORD_H
