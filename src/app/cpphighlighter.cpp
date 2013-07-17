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

#include "cpphighlighter.h"

cppHighlighter::cppHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
    //get textCharFormatMap instance
    instance = textCharFormatMap::getInstance();

    //Declare values:
    int i;
    highlight_rule hlrDataType, hlrKeyWords, hlrSpTypes,hlrSingleLineCComments;
    QString strKeyWords;

    //Set Data Types:
    hlrDataType.type_name="datatype";
    hlrDataType.regexp.setPattern("\\b(bool|char|double|float|int|long|short|signed|unsigned|void|wchar_t|char16_t|char32_t|nullptr)\\b");
    rules<<hlrDataType;

    //Set Key Words:
    hlrKeyWords.type_name="keyword";
    QStringList _keyword;
    _keyword<<"__asm|__cdecl|__declspec|__export|__far16|"
    <<"__fastcall|__fortran|__import|"
    <<"__pascal|__rtti|__stdcall|_asm|_cdecl|"
    <<"__except|_export|_far16|_fastcall|"
    <<"__finally|_fortran|_import|_pascal|_stdcall|__thread|__try|asm|auto|"
    <<"break|case|catch|cdecl|const|continue|default|"
    <<"do|else|enum|extern|for|goto|"
    <<"if|pascal|"
    <<"register|return|sizeof|static|"
    <<"struct|switch|"
    <<"typedef|union|"
    <<"volatile|while|"
    <<"class|const_cast|delete|"
    <<"dynamic_cast|explicit|false|friend|"
    <<"inline|mutable|namespace|new|operator|private|protected|"
    <<"public|reinterpret_cast|static_cast|"
    <<"template|this|throw|true|"
    <<"try|typeid|typename|"
    <<"using|virtual";
    strKeyWords="\\b(";
    for(i=0;i<_keyword.size();i++)
    {
        strKeyWords+=_keyword[i];
    }
    strKeyWords+=QString(")\\b");
    hlrKeyWords.regexp.setPattern(strKeyWords);
    rules<<hlrKeyWords;

    //Set Other Special Types:
    //Pre-Process
    hlrSpTypes.type_name = "preproc";
    hlrSpTypes.regexp.setPattern(QString("^[[:blank:]]*#([[:blank:]]*[[:word:]]*)"));
    rules<<hlrSpTypes;

    //TODO
    hlrSpTypes.type_name="todo";
    hlrSpTypes.regexp.setPattern(QString("(TODO|FIXME|BUG)([:]?)"));
    rules<<hlrSpTypes;

    //String
    hlrSpTypes.type_name="string";
    hlrSpTypes.regexp.setPattern("\"([^\"']*)\"");
    rules<<hlrSpTypes;

    //Single Line Comments, this must be the last one
    hlrSpTypes.type_name="comment";
    hlrSpTypes.regexp.setPattern(QString("//.{0,}"));
    rules<<hlrSpTypes;

}

void cppHighlighter::highlightBlock(const QString &text)
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
            match=rules[i].regexp.match(
                        text,
                        match.capturedEnd());
        }
    }
}
