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

#include "gdbmivalue.h"

static void skipCommas(const QChar *&begin, const QChar *end)
{
    while (*begin == ',' && begin != end)
        ++begin;
}

GdbMiValue GdbMiValue::operator [] (const char *_str_name) const
{
    int i=children.size();
    while(i--)
        if (children[i].name == _str_name)
            return children[i];

    return GdbMiValue();
}

GdbMiValue& GdbMiValue::operator += (const GdbMiValue& child)
{
    children.append(child);

    return *this;
}

QString GdbMiValue::getName() const
{
    return name;
}

void GdbMiValue::build(const QChar *&begin, const QChar *&end)
{
    switch(begin->toLatin1())
    {
    case '\"':
        parseConst(begin,end);
        break;
    case '[':
        parseList(begin,end);
        break;
    case '{':
        parseTuple(begin,end);
        break;
    default:
        for(;begin!=end;begin++)
        {
            if(*begin!='=')
                name+=*begin;
            else
                break;
        }

        begin++;//skip the '='

        switch(begin->toLatin1())
        {
        case '\"':
            parseConst(begin,end);
            break;
        case '[':
            parseList(begin,end);
            break;
        case '{':
            parseTuple(begin,end);
            break;
        default:
            qDebug()<<"error! GdbMiValue:unknow";
        }
    }
}

void GdbMiValue::parseConst(const QChar *&begin, const QChar *&end)
{
    type=Const;

    QByteArray _tmp;

    bool isEscape=false;
    int chars;
    uchar prod;

    for(begin++;begin<end;begin++)
    {
        if(!isEscape && *begin=='\"')
            break;

        if(!isEscape)
        {
            if(*begin != '\\')
                _tmp+=*begin;
            else
            {
                isEscape=true;
                chars = 0;
                prod = 0;
            }

        }
        else
        {
            char c=begin->toLatin1();
            switch(c)
            {
            case 'a':
                _tmp+= '\a';
                isEscape=false;
                break;
            case 'b':
                _tmp+= '\b';
                isEscape=false;
                break;
            case 'f':
                _tmp+= '\f';
                isEscape=false;
                break;
            case 'n':
                _tmp+= '\n';
                isEscape=false;
                break;
            case 'r':
                _tmp+= '\r';
                isEscape=false;
                break;
            case 't':
                _tmp+= '\t';
                isEscape=false;
                break;
            case 'v':
                _tmp+= '\v';
                isEscape=false;
                break;
            case '"':
                _tmp+= '"';
                isEscape=false;
                break;
            case '\\':
                _tmp+= '\\';
                isEscape=false;
                break;
            default:
            {

                if (c < '0' || c > '7')
                {
                    isEscape=false;
                    _tmp += prod;
                    --begin;
                    break;
                }
                prod = prod * 8 + c - '0';
                if (++chars == 3 || begin == end)
                {
                    _tmp += prod;
                    isEscape=false;
                }
            }
            }
        }

    }

    value=QString::fromUtf8(_tmp);

    if(begin+1 <end)
        begin++;    //skip "
}

void GdbMiValue::parseList(const QChar *&begin, const QChar *&end)
{
    begin++;    //skip [

    type=List;

    while(begin<end && *begin!=']')
    {
        GdbMiValue child;
        child.build(begin,end);
        children<<child;
    }

    if(begin+1 < end)
        begin++;    //skip ]
}

void GdbMiValue::parseTuple(const QChar* &begin, const QChar* &end)
{
    begin++;    //skip {

    type=Tuple;

    skipCommas(begin,end);
    while(begin < end && *begin!='}')
    {
        GdbMiValue child;
        child.build(begin,end);
        children<<child;
        skipCommas(begin,end);
    }

    if(begin+1 < end)
        begin++;    //skip }
}

QString GdbMiValue::getValue() const
{
    return value;
}
