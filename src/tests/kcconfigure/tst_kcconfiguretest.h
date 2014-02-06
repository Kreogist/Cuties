#ifndef TST_KCCONFIGURETEST_H
#define TST_KCCONFIGURETEST_H

#include <QtTest>

class KCHighlighterTest : public QObject
{
    Q_OBJECT

public:
    KCHighlighterTest();

private Q_SLOTS:
    void getAndSetValueTest();
    void getAndSetPathValueTest();
};
#endif //TST_KCCONFIGURETEST_H
