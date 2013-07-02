#include "kcitextsearcher.h"

void kciTextSearchWorker::run()
{
    for(QTextBlock i=document->begin();i.next().isValid();i=i.next())
    {
        QRegularExpressionMatch matchResult=regexp.match(i.text());

        if(matchResult.hasMatch())
        {
            searchResult _sr_tmp;
            _sr_tmp.lineNum=i.blockNumber();
            _sr_tmp.startPos=matchResult.capturedStart();
            emit oneResultReady(_sr_tmp);
        }
    }
}

kciTextSearcher::kciTextSearcher(QObject *parent) :
    QObject(parent)
{
    p_document=nullptr;
}

void kciTextSearcher::search()
{
    QRegularExpression regexp;

    if(!(flags & RegularExpress))
    {
        subString=QRegularExpression::escape(subString);
    }

    if(flags & WholeWord)
    {
        subString+="\\b";
        subString.prepend(QString("\\b"));
    }

    regexp.setPattern(subString);

    if(!(flags & MatchCase))
        regexp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    kciTextSearchWorker *_worker=new kciTextSearchWorker;
    _worker->document=p_document;
    _worker->regexp=regexp;
    connect(_worker,SIGNAL(oneResultReady(searchResult)),
            this,SLOT(receiveSingleResult(searchResult)));
    connect(_worker,SIGNAL(finished(QPrivateSignal)),SLOT(deleteLater()));
}



QTextDocument *kciTextSearcher::getDocument() const
{
    return p_document;
}

void kciTextSearcher::setDocument(QTextDocument *value)
{
    p_document = value;
}

QString kciTextSearcher::getSubString() const
{
    return subString;
}

void kciTextSearcher::setRegexp(const QString &value)
{
    subString = value;
}


int kciTextSearcher::getFlags() const
{
    return flags;
}

void kciTextSearcher::setFlags(int value)
{
    flags = value;
}

void kciTextSearcher::receiveSingleResult(searchResult result)
{
    resultList<<result;
}
