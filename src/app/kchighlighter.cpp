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

#include <QDebug>

#include "kchighlighter.h"

static char charNeedParentheses[]="{}[]()";

KCHighlighter::KCHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

void KCHighlighter::highlightBlock(const QString &text)
{
    /*
     * This function is used to associate KCTextBlockData with QTextBlock.
     * And then call KCHighlightBlock() which highlight the source code.
     */
    KCTextBlockData *data=static_cast<KCTextBlockData *>(currentBlockUserData());
    if(data==NULL)
    {
        data=new KCTextBlockData;
        setCurrentBlockUserData(data);
    }

    data->beginUsingSearchDatas();
    data->onBlockChanged();
    data->endUsingSearchDatas();

    /*
     * For quotation search, we need to search only one char.
     * But we need to search for two times.
     */

    data->resetQuotationInfos();
    quotationPaired=parseQuotationInfo(text, data);

    /*
     * For single line comment, we have a new way to check it.
     * Suppose there have a comment, and we only have to know
     * that whether there is in a pair of quatations. And
     * fortunately, the line comment can be at only the right.
     */
    if(quotationPaired>-1)
    {
        data->setLineCommentPos(text.indexOf("//", quotationPaired));
    }
    else
    {
        data->setLineCommentPos(-1);
    }

    data->resetParentheseInfos();
    for(int i=0,l=strlen(charNeedParentheses);
        i<l;
        i++)
    {
        parseParenthesesInfo(text,data,charNeedParentheses[i]);
    }

    KCHighlightBlock(text);
}

int KCHighlighter::parseQuotationInfo(const QString &text,
                                      KCTextBlockData *data)
{
    int firstIndex=text.indexOf('\"');
    if(firstIndex>-1)
    {
        int secondIndex;
        bool findRealSecond;
        while(firstIndex>-1)
        {
            if(text.at(firstIndex-1)==QChar('\\'))
            {
                firstIndex=text.indexOf('\"',firstIndex+1);
                continue;
            }
            findRealSecond=false;
            secondIndex=text.indexOf('\"', firstIndex+1);
            while((!findRealSecond) && secondIndex>-1)
            {
                if(text.at(secondIndex-1)==QChar('\\'))
                {
                    secondIndex=text.indexOf('\"', secondIndex+1);
                    continue;
                }
                findRealSecond=true;
            }
            data->insertQuotationInfo(firstIndex, secondIndex);
            /*
             * Here don't delete the if sentence.
             * If there're odd quotations, the second quotation will
             * be -1. This time firstIndex will search from 0. So we
             * need to check out whether it should search for the
             * firstIndex.
             */
            if(secondIndex==-1)
            {
                break;
            }
            firstIndex=text.indexOf('\"', secondIndex+1);
        }
        return secondIndex;
    }
    return -1;
}

void KCHighlighter::parseParenthesesInfo(const QString &text,
        KCTextBlockData *data,
        char character)
{
    int index=text.indexOf(character);
    while(index!=-1)
    {
        data->insertParenthesesInfo(index,character);
        index=text.indexOf(character,index+1);
    }
}
