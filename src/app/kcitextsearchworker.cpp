#include "kcitextsearchworker.h"

//======kciTextSearchWorker======
kciTextSearchWorker::kciTextSearchWorker()
{
    needQuit=false;
}

void kciTextSearchWorker::run()
{
    setCaseSensitive(isCaseSensitive);

    for(QTextBlock i=document->begin();i.isValid();i=i.next())
    {
        currBlockNumber=i.blockNumber();
        match(i.text());
    }

    exit(0);
}

QList<searchResult>* kciTextSearchWorker::getResults()
{
    return resultList;
}

void kciTextSearchWorker::setResults(QList<searchResult> *results)
{
    resultList=results;
}

void kciTextSearchWorker::setDocument(QTextDocument *value)
{
    document = value;
}

void kciTextSearchWorker::setIsCaseSensitive(bool value)
{
    isCaseSensitive = value;
}

void kciTextSearchWorker::quitWhenRequest()
{
    lock.lockForRead();
    if(needQuit)
    {
        lock.unlock();
        exit(0);
    }
    lock.unlock();
}

void kciTextSearchWorker::emitResult(int startPos, int length)
{
    searchResult _sr_tmp;
    _sr_tmp.lineNum=currBlockNumber;
    _sr_tmp.startPos=startPos;

    _sr_tmp.length=length;

    resultList->append(_sr_tmp);
}

//======kciTextSearchWorkerRegexp======
void kciTextSearchWorkerRegexp::setPattern(const QString &pattern)
{
    regexp.setPattern(pattern);
}

void kciTextSearchWorkerRegexp::setCaseSensitive(bool value)
{
    QRegularExpression::PatternOptions po=regexp.patternOptions();
    if(!value)
        po|=QRegularExpression::CaseInsensitiveOption;
    else
        po&=~QRegularExpression::CaseInsensitiveOption;

    regexp.setPatternOptions(po);
}

void kciTextSearchWorkerRegexp::match(const QString &text)
{
    QRegularExpressionMatchIterator matchResultIt=regexp.globalMatch(text);

    while(matchResultIt.hasNext())
    {
        quitWhenRequest();

        QRegularExpressionMatch match=matchResultIt.next();

        emitResult(match.capturedStart(),match.capturedLength());
    }
}

//======kciTextSearchWorkerStringMatcher
void kciTextSearchWorkerStringMatcher::setPattern(const QString &pattern)
{
    matcher.setPattern(pattern);
}

void kciTextSearchWorkerStringMatcher::setCaseSensitive(bool value)
{
    Qt::CaseSensitivity cs = (value) ? Qt::CaseSensitive : Qt::CaseInsensitive;

    matcher.setCaseSensitivity(cs);
}

void kciTextSearchWorkerStringMatcher::match(const QString &text)
{
    int length=matcher.pattern().length(),from=0;
    for(int i=matcher.indexIn(text,from);
        i!=-1;
        from=i+length,i=matcher.indexIn(text,from))
    {
        quitWhenRequest();
        emitResult(i,length);
    }
}
