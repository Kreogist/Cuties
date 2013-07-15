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

kciTextSearcher::kciTextSearcher(QObject *parent) :
    QObject(parent)
{
    p_document=nullptr;
    worker=nullptr;
    qRegisterMetaType<searchResult>("searchResult");
}

void kciTextSearcher::search()
{
    if(worker)
    {
        worker->lock.lockForWrite();
        worker->needQuit=true;
        worker->lock.unlock();
        worker->wait();
        delete worker;
    }

    if((flags & RegularExpress) || (flags & WholeWord))
    {
        worker=new kciTextSearchWorkerRegexp;

        if(!(flags & RegularExpress))
            subString=QRegularExpression::escape(subString);

        if(flags & WholeWord)
        {
            subString.prepend(QString("\\b("));
            subString.append(QString(")\\b"));
        }
    }
    else
    {
        worker=new kciTextSearchWorkerStringMatcher;
    }

    worker->setPattern(subString);

    worker->setIsCaseSensitive(flags & MatchCase);

    worker->setDocument(p_document);

    connect(worker,SIGNAL(finished()),this,SLOT(onWorkerFinished()));
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

void kciTextSearcher::onWorkerFinished()
{
    emit finished(worker->getResults());
}
