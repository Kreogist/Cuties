#include "kcitextsearcher.h"

void kciTextSearchWorker::run()
{
    if(regexp.isValid())
    {
        for(QTextBlock i=document->begin();i.isValid();i=i.next())
        {
            QRegularExpressionMatchIterator matchResultIt=regexp.globalMatch(i.text());

            while(matchResultIt.hasNext())
            {
                QRegularExpressionMatch match=matchResultIt.next();

                searchResult _sr_tmp;
                _sr_tmp.lineNum=i.blockNumber();
                _sr_tmp.startPos=match.capturedStart();
                _sr_tmp.length=match.capturedLength();

                emit oneResultReady(_sr_tmp);
            }
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
        //worker->deleteLater();
        delete worker;
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
        subString.prepend(QString("\\b("));
        subString.append(QString(")\\b"));
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
