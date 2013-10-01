/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCITEXTSEARCHER_H
#define KCITEXTSEARCHER_H

#define SEARCH_UNTIL_END_MARK -0xfffffff

#include <QRegularExpression>
#include <QStringMatcher>
#include <QTextBlock>
#include <QMutex>

#include "kcitextblockdata.h"

class kciTextSearcher : public QObject
{
    Q_OBJECT
public:
    kciTextSearcher();

    void search(const QTextBlock &begin,
                int lineCount,
                const unsigned long long &searchCode, const bool &forward);

    void setIsCaseSensitive(bool value);
    void setPatternString(const QString &pattern);

    void requireStop();

protected:
    virtual void setPattern(const QString &pattern) = 0;
    void recordResult(int startPos, int length);
    virtual void match(const QString &text) = 0;
    virtual void setCaseSensitive(bool value) = 0;

private:
    kciTextBlockData *currBlockData;
    bool isCaseSensitive;
    bool resetMark;

    QMutex quitLock;
    bool needQuit;
};

class kciTextSearcherRegexp : public kciTextSearcher
{
protected:
    void setPattern(const QString &pattern);
    void match(const QString &text);
    void setCaseSensitive(bool value);

private:
    QRegularExpression regexp;
};

class kciTextSearcherStringMatcher : public kciTextSearcher
{
protected:
    void setPattern(const QString &pattern);
    void match(const QString &text);
    void setCaseSensitive(bool value);

private:
    QStringMatcher matcher;
};

#endif // KCITEXTSEARCHER_H
