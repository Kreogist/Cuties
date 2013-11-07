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
    int singleCommentBound=text.indexOf("//");
    int firstIndex=text.indexOf('\"');
    bool needToCheckComment=!(singleCommentBound==-1);
    if(firstIndex>-1 && (needToCheckComment & (firstIndex < singleCommentBound)))
    {
        int secondIndex;
        bool findRealSecond;
        while(firstIndex>-1 && (needToCheckComment & (firstIndex < singleCommentBound)))
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
            if(secondIndex == -1)
            {
                /*
                 * Here it means: we have the first quotation, but
                 * we don't have the second one. so the '//' is still
                 * in a string. Ignore it.
                 */
                data->setLineCommentPos(-1);
                break;
            }
            /*
             * So here we do search a second quotation, we have to check
             * the quotation is forward of the comment line or behind.
             */
            if(secondIndex > singleCommentBound)
            {
                /*
                 * Here means the '//' is still in a string, but unlike above,
                 * this string has been finished. So Ignore it, and try to find
                 * next '//'.
                 */
                singleCommentBound=text.indexOf("//", secondIndex+1);
                needToCheckComment=!(singleCommentBound==-1);
            }
            firstIndex=text.indexOf('\"', secondIndex+1);
        }
        data->setLineCommentPos(singleCommentBound);
        data->setQuotationStatus(secondIndex);
        return secondIndex;
    }
    data->setLineCommentPos(singleCommentBound);
    data->setQuotationStatus(-1);
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
