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
            _sr_tmp.length=matchResult.capturedLength();
            emit oneResultReady(_sr_tmp);
        }
    }

    exit(0);
}

kciTextSearcher::kciTextSearcher(QObject *parent) :
    QObject(parent)
{
    p_document=nullptr;
    qRegisterMetaType<searchResult>("searchResult");
}

void kciTextSearcher::search()
{
    if(worker)
    {
        worker->exit();
        worker->deleteLater();
    }

    while(!resultList.isEmpty())
        resultList.removeFirst();

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

    worker=new kciTextSearchWorker;
    worker->document=p_document;
    worker->regexp=regexp;
    connect(worker.data(),SIGNAL(oneResultReady(searchResult)),
            this,SLOT(receiveSingleResult(searchResult)));

    connect(worker.data(),SIGNAL(finished()),this,SIGNAL(finished()));
    worker->start(QThread::NormalPriority);
}

void kciTextSearcher::setDocument(QTextDocument *value)
{
    p_document = value;
}

void kciTextSearcher::setSubString(const QString &value)
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
    qDebug()<<resultList.size();
}
