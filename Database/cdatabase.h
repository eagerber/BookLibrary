#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

class CDatabasePimpl;
class QSqlDatabase;

class CDatabase
{
public:
    CDatabase();
    ~CDatabase();

    QSqlDatabase& instance();
    void open(const QString filename);
    void close();

private:

    CDatabasePimpl *_pimpl;
};

#endif // DATABASE_H
