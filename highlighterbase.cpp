
#include <QApplication>

#include "highlighterbase.h"

QMap<QString, QTextCharFormat> highlighterBase::map;
bool highlighterBase::isInited=false;

highlighterBase::highlighterBase(QObject *parent) :
    QSyntaxHighlighter(parent)
{
    if(!isInited)
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
        else{
            qDebug()<<"highlighterBase: Can't not open default.style";
        }
    }
}

const QTextCharFormat& highlighterBase::operator[] (const QString& typeName)
{
    return map[typeName];
}

const QTextCharFormat& highlighterBase::getTextCharFormat(
        const QString &typeName)
{
    return map[typeName];
}

/*!
* \brief highlighterBase::parseStyleFileLine parse a line of the style file.
* \param str_line The line that will be parsed.
* \param lenth The lenth of the str_line.
* \return return true if the string has been parsed successufully.Otherwise return false.
*/
bool highlighterBase::parseStyleFileLine(char *str_line)
{
    //ignore the comment line
    if(str_line[0]=='#' || (str_line[0]=='/' && str_line[1]=='/'))
        return true;

    QStringList tmp=QString(str_line).split("=");

    if(tmp.size()>2)
        return false;

    QString elem1 = tmp[0].simplified();

    if(elem1.isEmpty())
        return true;    //skip the empty line1

    tmp[1]=tmp[1].split("//").at(0).simplified();

    if (tmp[1].at(0)!='$')
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
                QFont font=textFormat.font();
                font.setBold(true);
                textFormat.setFont(font);
            }
            else if(define[i] == "italic")
                textFormat.setFontItalic(true);
            else if(define[i].at(0)=='#')
            {
                Q_ASSERT(define[i].size()==7);

                int r=define[i].mid(1,2).toInt(),
                    g=define[i].mid(3,2).toInt(),
                    b=define[i].mid(5,2).toInt();
                textFormat.setForeground(QBrush(QColor(r,g,b)));
            }
            else
                qDebug()<<"highlighterbase:Unknow attitute";
        }

        map[elem1]=textFormat;
    }
    else
    {
        //elem1's text format is same as elem2
        QString elem2=tmp[1].mid(1).simplified();
        auto e2_iterator = map.find(elem2);
        if(e2_iterator != map.end())
            map[elem1]=e2_iterator.value();
        else
            qDebug()<<"highlighterbase:"<<elem2<<" hasn't been defined";
    }

    return true;
}
