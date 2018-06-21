#ifndef DATABASEADAPTER_H
#define DATABASEADAPTER_H

#include <QList>

#include "cbook.h"
#include "cdatabase.h"

class CDatabaseAdapter
{
public:
    CDatabaseAdapter();
    ~CDatabaseAdapter();

    QList<CBook> books();

private:
    QString _filename;
    CDatabase _db;
};

#endif // DATABASEADAPTER_H
