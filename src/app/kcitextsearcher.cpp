/*
 *  Copyright 2013 Kreogist Dev Team
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

//======kciTextSearchWorker======
kciTextSearcher::kciTextSearcher()
{
    resetMark=false;
}

void kciTextSearcher::search(const QTextBlock& begin,
                             int lineCount,
                             const unsigned long long int& searchCode)
{
    setCaseSensitive(isCaseSensitive);

    /*This is a "lazy-search" which means that we just search the part
     *of the document which is visiable for user. So we need to guarantee
     *that all the parts that user can see are searched. Because the editor
     *may not display the whole part of the first block. If we just let
     *lineCount-=i.lineCount() , some part which user could see won't
     *be searched. And that's why we let lineCount+=begin.lineCount(); first.
     *
     *For example: the editor display 4 lines
     *   [first block begin            | lineCount=4;(the editor can display
     *                                 |               4 lines)
     **********************************| lineCount-=4(first block->line count);
     *                                *|
     *               first block end] *|
     *   [second block]               *| lineCount-=1(second block->line count);
     *   [third block]                *| Because the lineCount<0 at that time,
     **********************************| the third block won't be searched.
     *
     * So we let lineCount+=begin.lineCount(); to avoid this.Search a little
     * more text won't take bad effect to our program's user experience
     */
    lineCount+=begin.lineCount();

    for(QTextBlock i=begin;i.isValid() && lineCount>=0;i=i.next())
    {
        currBlockData=(kciTextBlockData*)i.userData();
        lineCount-=i.lineCount();
        if(Q_UNLIKELY(currBlockData==NULL))
        {
            continue;
        }
        currBlockData->beginUsingDatas();
        if(currBlockData->isSearched(searchCode))
        {
            currBlockData->endUsingDatas();
            continue;
        }
        currBlockData->setSearchCode(searchCode);
        currBlockData->resetMatchedTextPositions();
        if(!resetMark)
            match(i.text());
        currBlockData->endUsingDatas();
    }
}

void kciTextSearcher::setPatternString(const QString &pattern)
{
    if(!pattern.isEmpty())
    {
        setPattern(pattern);
        resetMark=false;
    }
    else
        resetMark=true;
}

void kciTextSearcher::setIsCaseSensitive(bool value)
{
    isCaseSensitive = value;
}

void kciTextSearcher::recordResult(int startPos, int length)
{
    currBlockData->insertMatchedTextPositions(startPos,length);
}

//======kciTextSearchWorkerRegexp======
void kciTextSearcherRegexp::setPattern(const QString &pattern)
{
    regexp.setPattern(pattern);
}

void kciTextSearcherRegexp::setCaseSensitive(bool value)
{
    QRegularExpression::PatternOptions po=regexp.patternOptions();
    if(!value)
        po|=QRegularExpression::CaseInsensitiveOption;
    else
        po&=~QRegularExpression::CaseInsensitiveOption;

    regexp.setPatternOptions(po);
}

void kciTextSearcherRegexp::match(const QString &text)
{
    QRegularExpressionMatchIterator matchResultIt=regexp.globalMatch(text);

    while(matchResultIt.hasNext())
    {
        QRegularExpressionMatch match=matchResultIt.next();

        recordResult(match.capturedStart(),match.capturedLength());
    }
}

//======kciTextSearchWorkerStringMatcher
void kciTextSearcherStringMatcher::setPattern(const QString &pattern)
{
    matcher.setPattern(pattern);
}

void kciTextSearcherStringMatcher::setCaseSensitive(bool value)
{
    Qt::CaseSensitivity cs = (value) ? Qt::CaseSensitive : Qt::CaseInsensitive;

    matcher.setCaseSensitivity(cs);
}

void kciTextSearcherStringMatcher::match(const QString &text)
{
    int length=matcher.pattern().length(),from=0;
    for(int i=matcher.indexIn(text,from);
        i!=-1;
        from=i+length,i=matcher.indexIn(text,from))
    {
        recordResult(i,length);
    }
}

