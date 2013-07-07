/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        worker->quit();
        worker->wait();
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
