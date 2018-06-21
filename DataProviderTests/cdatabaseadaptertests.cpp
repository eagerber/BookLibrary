#include <QCoreApplication>

#include <QtTest/QtTest>
#include <QFile>

#include "cdatabaseadapter.h"

class CDatabaseAdapterTests: public QObject
{
    Q_OBJECT
private slots:
    void create();
};

void CDatabaseAdapterTests::constructor()
{
    QString filename = "TestDatabase.sqlite";
    CDatabaseAdapter databaseAdapter(filename);

    QFile::remove(filename);
}

QTEST_MAIN(CDatabaseAdapterTests)
#include "cdatabaseadaptertests.moc"
