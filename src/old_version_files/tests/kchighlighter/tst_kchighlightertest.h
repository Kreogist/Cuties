#ifndef TST_KCCONFIGURETEST_H
#define TST_KCCONFIGURETEST_H

#include <QtTest>
#include <QVector>
#include <QString>
#include <QTextDocument>

#include "kchighlighter.h"
#include "kctextblockdata.h"

class KCHighlighterTest : public KCHighlighter
{
    Q_OBJECT

public:
    KCHighlighterTest();

private Q_SLOTS:
    void parseParenthesesInfoTest();
    void parseQuotationInfoTest();
};
#endif //TST_KCCONFIGURETEST_H
