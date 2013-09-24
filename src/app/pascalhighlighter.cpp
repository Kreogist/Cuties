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


#include "pascalhighlighter.h"

pascalHighlighter::pascalHighlighter(QObject *parent) :
    kciHighlighter(parent)
{
    //get textCharFormatMap instance
    instance = textCharFormatMap::getInstance();

    //Declare values:
    highlight_rule hlrDataType, hlrKeyWords, hlrSpTypes,hlrSingleLineCComments;
    QString strKeyWords;

    //Set Data Types:
    hlrDataType.type_name="datatype";
    hlrDataType.regexp.setPattern("\\b(boolean|byte|char|integer|maxint|real)\\b");
    hlrDataType.regexp.setPatternOptions(
                QRegularExpression::CaseInsensitiveOption);
    rules<<hlrDataType;

    //Set Key Words:
    hlrKeyWords.type_name="keyword";
    QStringList _keyword;
    _keyword<<"alfa|and|array|begin|case|const|div|"
            <<"do|downto|else|end|false|file|for|function|get|goto|if|in|"
            <<"label|mod|new|not|of|or|pack|packed|page|program|"
            <<"put|procedure|read|readln|record|repeat|reset|rewrite|set|"
            <<"text|then|to|true|type|unpack|until|var|while|with|writeln|write";
    strKeyWords="\\b(";
    for(int i=0;i<_keyword.size();i++)
    {
        strKeyWords+=_keyword[i];
    }
    strKeyWords+=QString(")\\b");
    hlrKeyWords.regexp.setPattern(strKeyWords);
    hlrKeyWords.regexp.setPatternOptions(
                QRegularExpression::CaseInsensitiveOption);
    rules<<hlrKeyWords;

    //Set Other Special Types:

    //TODO
    hlrSpTypes.type_name="todo";
    hlrSpTypes.regexp.setPattern(QString("(TODO|FIXME|BUG)([:]?)"));
    rules<<hlrSpTypes;

    //String
    hlrSpTypes.type_name="string";
    hlrSpTypes.regexp.setPattern("\"([^\"']*)\"");
    rules<<hlrSpTypes;

    hlrSpTypes.regexp.setPattern("\'([^\"']*)\'");
    rules<<hlrSpTypes;
}

void pascalHighlighter::kciHighlightBlock(const QString &text)
{
    //!TODO: unsupport multiline comment
    for(int i=0;i<rules.size();i++)
    {
        QRegularExpressionMatchIterator matchIterator=rules[i].regexp.globalMatch(
                    text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match=matchIterator.next();
            setFormat(match.capturedStart(),
                      match.capturedLength(),
                      instance->getTextCharFormat(rules[i].type_name));
        }
    }

    kciTextBlockData *data=(kciTextBlockData*)currentBlockUserData();

    Q_ASSERT(data!=NULL);

    QTextBlock prevBlock=currentBlock().previous();

    int baseLevel=0;
    if(prevBlock.isValid())
    {
        kciTextBlockData *prevData=(kciTextBlockData*)prevBlock.userData();
        Q_ASSERT(prevData!=NULL);
        baseLevel=prevData->getCodeLevel();

        if(prevBlock.text().contains(QRegularExpression("\\b(begin)\\b")))
            baseLevel++;
        else if(prevBlock.text().contains(QRegularExpression("\\b(end)\\b")))
            baseLevel--;
    }
    data->setCodeLevel(baseLevel);

}
