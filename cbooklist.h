#ifndef CDUPLICATEDBOOKRECORD_H
#define CDUPLICATEDBOOKRECORD_H

#include <QOBject>
#include <QList>

#include "cbook.h"

class CBookList : public CBook
{
    Q_OBJECT

public:
    explicit CBookList();
    CBookList(const CBookList &rValue);

    CBookList(const int id, const QString &name, const QString &fullPath);

    void addDuplicate(const CBook &duplicate);
    CBook& at(const int index);

    int length() const;

    QStringList toStringList();

private:
    QList<CBook> _books;
};

#endif // CDUPLICATEDBOOKRECORD_H
