#ifndef CLIBRARY_H
#define CLIBRARY_H

#include <QList>
#include <QMultiMap>
#include <QStringList>

#include "cbook.h"

using LibraryMap = QMultiMap<QByteArray, CBook>;

class CLibrary
{

public:
    CLibrary();

    void add(const CBook& book);
    // TODO: tests
    void remove(const CBook& book);

    // TODO: tests
    void addRange(const QList<CBook>& book);
    // TODO: tests
    int count() const;
    // TODO: tests
    const CBook& at(int n);
    // TODO: tests
    int maxIndex();
    // TODO: tests
    QList<CBook*> data();

    QList<CBook*> doppelgangers(const CBook& book);
    QList<CBook*> doppelgangers();

    // TODO: tests
    void deleteDuplicates();

    void normalize(const CBook& book, const QString truePath = 0);

    void removeNonExistentFiles();

    QStringList availableExtensions();

    void replaceBook(CBook& book, QString path, bool deleteSource = false);

private:    
    void deleteFile(const QString &filename);

    LibraryMap _data;
};

#endif // CLIBRARY_H
