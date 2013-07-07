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

#ifndef KCITEXTSEARCHER_H
#define KCITEXTSEARCHER_H

#include <QObject>
#include <QThread>
#include <QRegularExpression>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegularExpressionMatch>
#include <QList>
#include <QPointer>
#include <QReadWriteLock>
#include <QDebug>

struct searchResult
{
    int lineNum;
    int startPos;
    int length;
};

class kciTextSearchWorker : public QThread
{
    Q_OBJECT
public:
    QRegularExpression regexp;
    QTextDocument* document;

protected:
    void run();

signals:
    void oneResultReady(searchResult result);

};

class kciTextSearcher : public QObject
{
    Q_OBJECT
public:
    enum seacherFlags
    {
        RegularExpress =   0x1,
        MatchCase =        0x2,
        WholeWord =        0x4
    };

    explicit kciTextSearcher(QObject *parent = 0);

    void search();

    void setDocument(QTextDocument *value);
    void setSubString(const QString &value);
    int getFlags() const;
    void setFlags(int value);

    QList<searchResult> resultList;
    QReadWriteLock lock;

signals:
    void finished();
    
public slots:
    void receiveSingleResult(searchResult result);
    
private:
    QString subString;
    QTextDocument* p_document;
    int flags;
    QPointer<kciTextSearchWorker> worker;
};

#endif // KCITEXTSEARCHER_H
