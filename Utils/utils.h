#ifndef UTILS_H
#define UTILS_H

#include "utils_global.h"

#include <QString>
#include <QFileInfo>

class UTILSSHARED_EXPORT Utils
{

public:
    static QString uniqueDatabaseName();
    static void deleteFile(const QString &filename);
    static QFileInfo replaceFile(const QString &path, const QString &newPath);

private:
    Utils();
    ~Utils();
};

#endif // UTILS_H
