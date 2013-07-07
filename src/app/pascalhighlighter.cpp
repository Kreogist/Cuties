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

#include "pascalhighlighter.h"

pascalHighlighter::pascalHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
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
    _keyword<<"alfa|and|array|begin|case|const|div"
            <<"do|downto|else|end|false|file|for|function|get|goto|if|in"
            <<"label|mod|new|not|of|or|pack|packed|page|program"
            <<"put|procedure|read|readln|record|repeat|reset|rewrite|set"
            <<"text|then|to|true|type|unpack|until|var|while|with|writeln|write";
    strKeyWords="\\b(";
    for(int i=0;i<_keyword.size();i++)
    {
        strKeyWords=strKeyWords+_keyword[i];
    }
    strKeyWords=strKeyWords+QString(")\\b");
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

QRegularExpression pascalHighlighter::suffixFilter()
{
    return QRegularExpression("pas",QRegularExpression::CaseInsensitiveOption);
}

void pascalHighlighter::highlightBlock(const QString &text)
{
    //!TODO: unsupport multiline comment
    for(int i=0;i<rules.size();i++)
    {
        QRegularExpressionMatch match=rules[i].regexp.match(
                    text,
                    0);
        while (match.hasMatch()) {
            setFormat(match.capturedStart(),
                      match.capturedLength(),
                      instance->getTextCharFormat(rules[i].type_name));
            match=rules[i].regexp.match(
                        text,
                        match.capturedEnd());
        }
    }
}
