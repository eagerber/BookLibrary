#include <QCoreApplication>

#include <QtTest/QtTest>

class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void toUpper_data();
    void toUpper();
};

void TestQString::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";

}

void TestQString::toUpper()
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

QTEST_MAIN(TestQString)
#include "main.moc"

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//
//    return a.exec();
//}
