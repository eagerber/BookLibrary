#include <QCoreApplication>

#include <QtTest/QtTest>

class CDatabaseAdapterTests: public QObject
{
    Q_OBJECT
private slots:
    void toUpper_data();
    void toUpper();
};

void CDatabaseAdapterTests::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";

}

void CDatabaseAdapterTests::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    if(string == "HELLO")
    {
        QSKIP("");
    };

    QBENCHMARK
    {
    QCOMPARE(string.toUpper(), result);
    }
}

QTEST_MAIN(CDatabaseAdapterTests)
#include "cdatabaseadaptertests.moc"
