#include <QtTest/QtTest>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QUuid>
#include <QDebug>

#include "cdatabase.h"


class CDatabaseTests: public QObject
{
    Q_OBJECT
private slots:
//    void toUpper_data();
//    void toUpper();

    void openDatabase();
    void createDatabase();
    void createDatabaseException();
    void execQuery();

private:
    QString UniqueDatabaseName();
};

//void CDatabaseTests::toUpper_data()
//{
//    QTest::addColumn<QString>("string");
//    QTest::addColumn<QString>("result");
//
//    QTest::newRow("all lower") << "hello" << "HELLO";
//    QTest::newRow("mixed")     << "Hello" << "HELLO";
//    QTest::newRow("all upper") << "HELLO" << "HELLO";
//
//    QSKIP("Skip it");
//}
//
//void CDatabaseTests::toUpper()
//{
//    QFETCH(QString, string);
//    QFETCH(QString, result);
//
//    QBENCHMARK
//    {
//    QCOMPARE(string.toUpper(), result);
//    }
//}

void CDatabaseTests::openDatabase()
{
    QString filename = UniqueDatabaseName();

    QFile::copy(":/resource/TestDatabase.sqlite", filename);
    QFile::setPermissions(filename, QFile::ReadOwner | QFile::WriteOwner);

    CDatabase db;
    db.open(filename);
    db.close();

    QFile::remove(filename);
}

void CDatabaseTests::createDatabase()
{
    QString filename = UniqueDatabaseName();

    CDatabase db;
    db.open(filename);
    db.close();

    bool fileExists = QFile::exists(filename);
    QFile::remove(filename);

    QVERIFY(fileExists);
}

void CDatabaseTests::createDatabaseException()
{
    CDatabase db;
    QVERIFY_EXCEPTION_THROWN(db.open(".\\NonexistentDirectory\\TestDatabase.sqlite"), QException);
    db.close();
}

void CDatabaseTests::execQuery()
{
    QString filename = UniqueDatabaseName();

    CDatabase db;
    db.open(filename);

    QList<int> expectedId;
    QList<QString> expectedFullPath;
    QList<QString> expectedName;
    QList<QString> expectedExtension;
    QList<int> expectedSize;
    QList<QByteArray> expectedHash;

    int expectedRecordsCount = 5;
    for(int i = 0; i < expectedRecordsCount; ++i)
    {
        expectedId.push_back(i);
        expectedFullPath.push_back(QString("FullPath %1").arg(i));
        expectedName.push_back(QString("name %1").arg(i));
        expectedExtension.push_back(QString("Ext %1").arg(i));
        expectedSize.push_back(rand());
        expectedHash.push_back(QUuid::createUuid().toByteArray());
    }

    QSqlQuery insertQuery(db.instance());
    insertQuery.prepare("INSERT INTO Catalog (Id, FullPath, Name, Extension, Size, MD5) VALUES(:Id, :FullPath,:Name,:Extension,:Size,:MD5);");

    for(int i = 0; i < expectedRecordsCount; ++i)
    {
        insertQuery.bindValue(":Id", expectedId[i]);
        insertQuery.bindValue(":FullPath", expectedFullPath[i]);
        insertQuery.bindValue(":Name", expectedName[i]);
        insertQuery.bindValue(":Extension", expectedExtension[i]);
        insertQuery.bindValue(":Size", expectedSize[i]);
        insertQuery.bindValue(":MD5", expectedHash[i]);

        insertQuery.exec();
    }

    QSqlQuery selectQuery(db.instance());
    selectQuery.prepare("SELECT Id, FullPath, Name, Extension, Size, MD5 FROM Catalog ORDER BY Id;");

    int index = 0;
    while(selectQuery.next())
    {
        QVERIFY(index < expectedRecordsCount);
        QCOMPARE(expectedId[index], selectQuery.value(0).toInt());
        QCOMPARE(expectedFullPath[index], selectQuery.value(1).toString());
        QCOMPARE(expectedName[index], selectQuery.value(2).toString());
        QCOMPARE(expectedExtension[index], selectQuery.value(3).toString());
        QCOMPARE(expectedSize[index], selectQuery.value(4).toInt());
        QCOMPARE(expectedHash[index], selectQuery.value(5).toByteArray());

        QCOMPARE(expectedId[index], selectQuery.value("Id").toInt());
        QCOMPARE(expectedFullPath[index], selectQuery.value("FullPath").toString());
        QCOMPARE(expectedName[index], selectQuery.value("Name").toString());
        QCOMPARE(expectedExtension[index], selectQuery.value("Extension").toString());
        QCOMPARE(expectedSize[index], selectQuery.value("Size").toInt());
        QCOMPARE(expectedHash[index], selectQuery.value("MD5").toByteArray());

        ++index;
    }
    QSqlQuery deleteQuery(db.instance());
    deleteQuery.prepare("DELETE FROM Catalog");
    deleteQuery.exec();

    selectQuery.clear();
    selectQuery.prepare("SELECT * FROM Catalog ORDER BY Id;");
    selectQuery.exec();

    index = 0;
    while(selectQuery.next())
    {
        index++;
    }

    QCOMPARE(0, index);

    db.close();

    QFile::remove(filename);
}


QString CDatabaseTests::UniqueDatabaseName()
{
    QString uuid = QUuid::createUuid().toString();
    uuid = uuid.mid(1, uuid.length() - 2);
    return uuid + ".sqlite";
}

QTEST_MAIN(CDatabaseTests)
#include "cdatabasetests.moc"
