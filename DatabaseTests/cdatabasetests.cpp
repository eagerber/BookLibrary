#include <QtTest/QtTest>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "cdatabase.h"


class CDatabaseTests: public QObject
{
    Q_OBJECT
private slots:
    void toUpper_data();
    void toUpper();

    void createDatabase();
    void createDatabaseException();
};

void CDatabaseTests::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";

    QSKIP("Skip it");
}

void CDatabaseTests::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QBENCHMARK
    {
    QCOMPARE(string.toUpper(), result);
    }
}

void CDatabaseTests::createDatabase()
{
    CDatabase db;
    db.open("TestDatabase.sqlite");
    db.close();
}

void CDatabaseTests::createDatabaseException()
{
    CDatabase db;
    QVERIFY_EXCEPTION_THROWN(db.open(".\\SomeDirectory\\TestDatabase.sqlite"), QException);
    db.close();
}

QTEST_MAIN(CDatabaseTests)
#include "cdatabasetests.moc"
