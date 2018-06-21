#ifndef CBOOK_H
#define CBOOK_H

#include <QObject>
#include <QString>

class CBook : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString fullPath READ fullPath)

public:
    explicit CBook();
    CBook(const CBook &rValue);

    CBook(const int id, const QString &name, const QString &fullPath);
    ~CBook();

    CBook& operator= (const CBook& rValue);

    int id() const;
    QString name() const;
    QString fullPath() const;

private:
    int _id;
    QString _name;
    QString _fullPath;
};

#endif // CBOOK_H
