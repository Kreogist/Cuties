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

#include "kchighlighter.h"

static char charNeedParentheses[]="{}[]()";

KCHighlighter::KCHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

void KCHighlighter::highlightBlock(const QString &text)
{
    /* This function is used to associate KCTextBlockData with QTextBlock.
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

    data->resetParentheseInfos();
    for(int i=0,l=strlen(charNeedParentheses);
        i<l;
        i++)
    {
        parseParenthesesInfo(text,data,charNeedParentheses[i]);
    }

    KCHighlightBlock(text);
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
