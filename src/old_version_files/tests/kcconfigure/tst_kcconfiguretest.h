#ifndef TST_KCCONFIGURETEST_H
#define TST_KCCONFIGURETEST_H

#include <QtTest>

#include "kcconfigure.h"

class KCConfigureForTest : public KCConfigure
{
protected:
    QString getGroupName() const;
};

class KCConfigureTest : public QObject
{
    Q_OBJECT

public:
    KCConfigureTest();

private Q_SLOTS:
    void getAndSetValueTest();
    void getAndSetPathValueTest();
};
#endif //TST_KCCONFIGURETEST_H
