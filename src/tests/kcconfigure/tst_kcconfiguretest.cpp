#include <QCoreApplication>

#include "tst_kcconfiguretest.h"
#include "kcconfigure.h"

KCHighlighterTest::KCHighlighterTest()
{
}

void KCHighlighterTest::getAndSetValueTest()
{
    KCConfigure configure;

    configure.setValue("test","testvalue");
    QCOMPARE(configure.getValue("test").toString(),QString("testvalue"));
    configure.setValue("te_st","test__value");
    QCOMPARE(configure.getValue("te_st").toString(),QString("test__value"));
    configure.setValue("te st","test value");
    QCOMPARE(configure.getValue("te st").toString(),QString("test value"));
    configure.setValue("Test","testValue");
    QCOMPARE(configure.getValue("Test").toString(),QString("testValue"));
    configure.setValue("Te st_test","testvalue");
    QCOMPARE(configure.getValue("Te st_test").toString(),QString("testvalue"));
    configure.setValue("test","testvalue2");
    QCOMPARE(configure.getValue("test").toString(),QString("testvalue2"));
}

void KCHighlighterTest::getAndSetPathValueTest()
{
    KCConfigure configure;

    configure.setPathValue("aaapath","testpath");
    QCOMPARE(configure.getValue("aaapath").toString(),QString("testpath"));
}

QTEST_MAIN(KCHighlighterTest)

//#include "tst_kcconfiguretest.moc"
