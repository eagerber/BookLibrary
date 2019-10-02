#ifndef CLIBRARY_H
#define CLIBRARY_H

#include <QList>
#include <QMap>
#include <QStringList>

#include "cbook.h"

class CLibrary
{
public:
    CLibrary();

    void add(const CBook& book);
    // TODO: tests
    void remove(const CBook& book);
    // TODO: tests
    void remove(int index);

    // TODO: tests
    void addRange(const QList<CBook>& book);
    // TODO: tests
    int count();
    // TODO: tests
    CBook& operator[](int n);
    // TODO: tests
    const CBook& at(int n);
    // TODO: tests
    int maxIndex();
    // TODO: tests
    QList<CBook>& data();

    QList<CBook> doppelgangers(CBook& book);
    QList<CBook> doppelgangers();

    // TODO: tests
    void deleteDuplicates();

    void normalize(const CBook& book, const QString truePath = 0);

    void removeNonExistentFiles();

    QStringList availableExtensions();

    void replaceBook(CBook& book, QString path, bool deleteSource = false);

private:    
    void deleteFile(const QString &filename);

    QList<CBook> _data;
    QMap<QByteArray, QList<CBook*>> _doppelgangers;

};

#endif // CLIBRARY_H
