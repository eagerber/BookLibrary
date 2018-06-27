#ifndef CBOOK_H
#define CBOOK_H

#include <QObject>
#include <QString>
#include <QByteArray>

class CBook;

uint qHash(const CBook &val);

class CBook : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString fullPath READ fullPath)
    Q_PROPERTY(QString extension READ extension)
    Q_PROPERTY(int size READ size)
    Q_PROPERTY(QByteArray md5 READ md5)

public:
    explicit CBook();
    CBook(const CBook &rValue);

    CBook(
        const int id,
        const QString &name,
        const QString &fullPath,
        const QString &extension,
        const int &size,
        const QByteArray &md5);
    ~CBook();

    CBook& operator= (const CBook& rValue);
    bool operator== (const CBook& rValue) const;
    bool HashSumMatch(const CBook& rValue) const;

    int id() const;
    QString name() const;
    QString fullPath() const;
    QString extension() const;
    int size() const;
    QByteArray md5() const;


private:
    int _id;
    QString _name;
    QString _fullPath;
    QString _extension;
    int _size;
    QByteArray _md5;
};

#endif // CBOOK_H
