#ifndef CBOOKRECORD_H
#define CBOOKRECORD_H

#include <QObject>
#include <QString>

class CBookRecord : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString fullPath READ fullPath)

public:
    explicit CBookRecord();
    CBookRecord(const CBookRecord &rValue);

    CBookRecord(const int id, const QString &name, const QString &fullPath);
    ~CBookRecord();

    int id() const;
    QString name() const;
    QString fullPath() const;

private:
    int _id;
    QString _name;
    QString _fullPath;
};
#endif // CBOOKRECORD_H
