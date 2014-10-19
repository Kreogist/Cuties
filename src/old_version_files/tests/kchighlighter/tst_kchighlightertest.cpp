#include <QCoreApplication>

#include "tst_kchighlightertest.h"

KCHighlighterTest::KCHighlighterTest():
    KCHighlighter(new  QTextDocument)
{
}

void KCHighlighterTest::parseParenthesesInfoTest()
{

    struct testData
    {
        QString _text;
        QByteArray _ch;
        QString _c_result;
        QVector<int> _i_result;
        testData(){}
        testData(QString text,QByteArray ch,QString c_result,QVector<int> i_result):
            _text(text),
            _ch(ch),
            _c_result(c_result),
            _i_result(i_result)
        {
        }
    };

    QVector<testData> datas;
    datas<<(testData("(abcdd(())","()","((())",QVector<int>()<<0<<6<<7<<8<<9))
         <<(testData(")(][}{","([}{])",")(][}{",QVector<int>()<<0<<1<<2<<3<<4<<5))
         <<(testData(")(][}{[][","[]","][[][",QVector<int>()<<2<<3<<6<<7<<8));

    for(int i=0;i<datas.size();i++)
    {
        KCTextBlockData data;
        for(int j=0;j<datas[i]._ch.size();j++)
        {
            KCHighlighter::parseParenthesesInfo(datas[i]._text,&data,datas[i]._ch.at(j));
        }
        auto p_c=datas[i]._c_result.begin();
        auto p_i=datas[i]._i_result.begin();
        for(auto j=data.getFirstParenthesesInfo();
            j!=data.getEndParenthesesInfo();
            j++)
        {
            QVERIFY(*p_c!=QChar('\0'));
            QCOMPARE(QChar(j->character),*p_c++);
            QCOMPARE(j->pos,*p_i++);
        }
    }
}

void KCHighlighterTest::parseQuotationInfoTest()
{
    struct quote
    {
        int begin;
        int end;
        quote(){}
        quote(int a,int b):
            begin(a),
            end(b)
        {

        }
    };
    struct testData
    {
        QString _text;
        QVector<quote> _result;
        testData(){}
        testData(QString text,QVector<quote> result):
            _text(text),
            _result(result)
        {
        }
    };

    QVector<testData> datas;
    datas<<(testData("abcde\"test\"GNU",QVector<quote>()<<quote(5,11)))
         <<(testData("abcde\"test\"G\"NU\"",QVector<quote>()<<quote(5,11)<<quote(12,16)))
         <<(testData("abcde\"t\\et\"G\"NU\"",QVector<quote>()<<quote(5,11)<<quote(12,16)))
         <<(testData("abcde//t\"et\"G\"NU\"",QVector<quote>()))
         <<(testData("abcde\"e//t\"G\"NU\"",QVector<quote>()<<quote(5,11)<<quote(12,16)));

    for(int i=0;i<datas.size();i++)
    {
        KCTextBlockData data;
        KCHighlighter::parseQuotationInfo(datas[i]._text,&data);
        auto p=datas[i]._result.begin();
        for(auto j=data.getFirstQuotationInfo();
            j!=data.getEndQuotationInfo();
            j++)
        {
            QVERIFY(p!=datas[i]._result.end());
            QCOMPARE(j->beginPos,p->begin);
            QCOMPARE(j->endPos,(*p++).end);
        }
    }
}

QTEST_MAIN(KCHighlighterTest)

//#include "tst_kcconfiguretest.moc"
