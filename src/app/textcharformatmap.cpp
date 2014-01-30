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


#include "textcharformatmap.h"

textCharFormatMap *textCharFormatMap::instance=nullptr;

textCharFormatMap::textCharFormatMap(QObject *parent) :
    QObject(parent)
{
    /*--------------Solve the very exotic problem.----------------*/
    //QFile file("default.style");
    QFile file(qApp->applicationDirPath() + "/default.style");

    if(file.open(QFile::ReadOnly| QFile::Text))
    {
        char str_line[100];

        for(int i=file.readLine(str_line,100);
            i>0;
            i=file.readLine(str_line,100))
        {
            parseStyleFileLine(str_line);
        }

    }
    else
    {
        qDebug()<<"textCharFormatMap: Can't not open default.style";
    }
}

textCharFormatMap *textCharFormatMap::getInstance()
{
    //FIXME: This isn't thread-safe
    if(instance == nullptr)
    {
        instance = new textCharFormatMap;
    }

    return instance;
}


const QTextCharFormat &textCharFormatMap::getTextCharFormat(
    const QString &typeName)
{
    return map[typeName];
}

/*!
* \brief textCharFormatMap::parseStyleFileLine parse a line of the style file.
* \param str_line The line that will be parsed.
* \param lenth The lenth of the str_line.
* \return return true if the string has been parsed successufully.Otherwise return false.
*/
bool textCharFormatMap::parseStyleFileLine(char *str_line)
{
    //ignore the comment line
    if(str_line[0]=='#' || (str_line[0]=='/' && str_line[1]=='/'))
    {
        return true;
    }

    QStringList tmp=QString(str_line).split("=");

    if(tmp.size()>2)
    {
        return false;
    }

    QString elem1 = tmp[0].simplified();

    if(elem1.isEmpty())
    {
        return true;    //skip the empty line1
    }

    tmp[1]=tmp[1].split("//").at(0).simplified();

    if(tmp[1].at(0)!='$')
    {
        //It's a defination of the elem1's text format.
        //First, split the comment part
        //Then, split by ','
        QStringList define=tmp[1].split("//").at(0).split(",");

        QTextCharFormat textFormat;
        int i=define.size();
        while(i--)
        {
            define[i]=define[i].simplified();
            if(define[i] == "bold")
            {
                QFont font=KCFontConfigure::getInstance()->getCodeFont();
                font.setBold(true);
                textFormat.setFont(font);
            }
            else if(define[i] == "italic")
            {
                textFormat.setFontItalic(true);
            }
            else if(define[i].at(0)=='#')
            {
                Q_ASSERT(define[i].size()==7);

                bool blnHexOk;
                int r=define[i].mid(1,2).toInt(&blnHexOk, 16),
                    g=define[i].mid(3,2).toInt(&blnHexOk, 16),
                    b=define[i].mid(5,2).toInt(&blnHexOk, 16);
                textFormat.setForeground(QBrush(QColor(r,g,b)));
            }
            else
            {
                qDebug()<<"highlighterbase:Unknow attitute";
            }
        }

        map[elem1]=textFormat;
    }
    else
    {
        //elem1's text format is same as elem2
        QString elem2=tmp[1].mid(1).simplified();
        auto e2_iterator = map.find(elem2);
        if(e2_iterator != map.end())
        {
            map[elem1]=e2_iterator.value();
        }
        else
        {
            qDebug()<<"highlighterbase:"<<elem2<<" hasn't been defined";
        }
    }

    return true;
}
