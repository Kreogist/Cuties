/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
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
    parseQuotationInfo(text, data);

    data->resetParentheseInfos();
    for(int i=0,l=strlen(charNeedParentheses);
        i<l;
        i++)
    {
        parseParenthesesInfo(text,data,charNeedParentheses[i]);
    }

    KCHighlightBlock(text);
}

void KCHighlighter::parseQuotationInfo(const QString &text,
                                       KCTextBlockData *data)
{
    int firstIndex=text.indexOf('\"');
    int singleCommentPos=text.indexOf("//");
    bool needToCheckComment=(singleCommentPos!=-1);
    if(firstIndex>-1)
    {
        int secondIndex=0;
        bool findRealSecond;
        while(firstIndex>-1)
        {
            if(needToCheckComment == true && firstIndex>singleCommentPos)
            {
                /*
                 * Here, no need to check anymore, all of these will be comment.
                 */
                break;
            }
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
            data->insertQuotationInfo(firstIndex, secondIndex+1);
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
            if(secondIndex > singleCommentPos)
            {
                /*
                 * Here means the '//' is still in a string, but unlike above,
                 * this string has been finished. So Ignore it, and try to find
                 * next '//'.
                 */
                singleCommentPos=text.indexOf("//", secondIndex+1);
                needToCheckComment=!(singleCommentPos==-1);
            }
            firstIndex=text.indexOf('\"', secondIndex+1);
        }
        data->setLineCommentPos(singleCommentPos);
        data->setQuotationStatus(secondIndex);
        return;
    }
    data->setLineCommentPos(singleCommentPos);
    data->setQuotationStatus(-1);
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
