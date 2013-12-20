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

#include <QApplication>

#include "kccolorconfigure.h"

KCColorConfigure *KCColorConfigure::instance=nullptr;
QString KCColorConfigure::colorConfigFilePath("DefaultColorConfig.ini");

KCColorConfigure *KCColorConfigure::getInstance()
{
    return instance==nullptr?
           instance=new KCColorConfigure:instance;
}

KCColorConfigure::Color KCColorConfigure::parseColor(const QString &content)
{
    /* Cuties support using expression like "ColorName = #RRGGBB"(like html) to define a color:
     * For example:
     *     white = #000000
     */

    //first, remove all whitespace from the start and the end
    //and replace each sequence of internal whitespace with a single space
    QString simplifiedContent=content.simplified();

    //then, we check whether the first char is '#'
    if(simplifiedContent.at(0) == '#')
    {
        //last, we try to get the value of (r,g,b)
        Color ret;
        bool isOk=false;
        ret.r=simplifiedContent.mid(1,2).toInt(&isOk,16);
        if(!isOk)
        {
            qDebug()<<"KCConfigure Error: unknow color";
            return Color(-1,-1,-1);
        }
        ret.g=simplifiedContent.mid(3,2).toInt(&isOk,16);
        if(!isOk)
        {
            qDebug()<<"KCConfigure Error: unknow color";
            return Color(-1,-1,-1);
        }
        ret.b=simplifiedContent.mid(5,2).toInt(&isOk,16);
        if(!isOk)
        {
            qDebug()<<"KCConfigure Error: unknow color";
            return Color(-1,-1,-1);
        }

        return ret;
    }
    else
    {
        //unknow format,return error.
        qDebug()<<"KCConfigure Error: unknow format";
        return Color(-1,-1,-1);
    }
}

KCColorConfigure::Color KCColorConfigure::parseObjectColor(const QString &content)
{
    /* Cuties support two ways to define a object's color:
     * 1. ColorRole = #RRGGBB (like html)
     * 2. ColorRole = $ColorName
     * For example:
     *     WindowText = #000000
     *     WindowText = $white
     */

    //first, remove all whitespace from the start and the end
    //and replace each sequence of internal whitespace with a single space
    QString simplifiedContent=content.simplified();

    //then, we check the first character
    if(simplifiedContent.at(0) == '#')
    {
        return parseColor(simplifiedContent);
    }
    else if(simplifiedContent.at(0) == '$')
    {
        auto iteratorColor=colorSheet.find(simplifiedContent.mid(1));

        if(iteratorColor!=colorSheet.end())
        {
            return *iteratorColor;
        }
        else
        {
            qDebug()<<"KCConfigure Error: undefined color";
            return Color(-1,-1,-1);
        }
    }
    else
    {
        qDebug()<<"KCConfigure Error: unknow format";
        return Color(-1,-1,-1);
    }
}

QPalette::ColorRole KCColorConfigure::getColorRoleFromString(const QString &string)
{
    QString lowerString=string.toLower();
    if(lowerString == "window" || lowerString == "background")
    {
        return QPalette::Window;
    }

    if(lowerString == "windowtext" || lowerString == "foreground")
    {
        return QPalette::WindowText;
    }

    if(lowerString == "base")
    {
        return QPalette::Base;
    }

    if(lowerString == "alternatebase")
    {
        return QPalette::AlternateBase;
    }

    if(lowerString == "tooltipbase")
    {
        return QPalette::ToolTipBase;
    }

    if(lowerString == "tooltiptext")
    {
        return QPalette::ToolTipText;
    }

    if(lowerString == "text")
    {
        return QPalette::Text;
    }

    if(lowerString == "button")
    {
        return QPalette::Button;
    }

    if(lowerString == "buttontext")
    {
        return QPalette::ButtonText;
    }

    if(lowerString == "brighttext")
    {
        return QPalette::BrightText;
    }

    if(lowerString == "light")
    {
        return QPalette::Light;
    }

    if(lowerString == "midlight")
    {
        return QPalette::Midlight;
    }

    if(lowerString == "dark")
    {
        return QPalette::Dark;
    }

    if(lowerString == "mid")
    {
        return QPalette::Mid;
    }

    if(lowerString == "shadow")
    {
        return QPalette::Shadow;
    }

    if(lowerString == "highlight")
    {
        return QPalette::Highlight;
    }

    if(lowerString == "highlightedtext")
    {
        return QPalette::HighlightedText;
    }

    if(lowerString == "link")
    {
        return QPalette::Link;
    }

    if(lowerString == "linkvisited")
    {
        return QPalette::LinkVisited;
    }

    return QPalette::NoRole;
}

QString KCColorConfigure::getColorRoleString(QPalette::ColorRole role)
{
    switch(role)
    {
    case QPalette::Window:
        return QString("Window");
    case QPalette::WindowText:
        return QString("WindowText");
    case QPalette::Base:
        return QString("Base");
    case QPalette::AlternateBase:
        return QString("AlternateBase");
    case QPalette::ToolTipBase:
        return QString("ToolTipBase");
    case QPalette::ToolTipText:
        return QString("ToolTipText");
    case QPalette::Text:
        return QString("Text");
    case QPalette::Button:
        return QString("Button");
    case QPalette::ButtonText:
        return QString("ButtonText");
    case QPalette::BrightText:
        return QString("BrightText");
    case QPalette::Light:
        return QString("Light");
    case QPalette::Midlight:
        return QString("Midlight");
    case QPalette::Dark:
        return QString("Dark");
    case QPalette::Mid:
        return QString("Mid");
    case QPalette::Shadow:
        return QString("Shadow");
    case QPalette::Highlight:
        return QString("Highlight");
    case QPalette::HighlightedText:
        return QString("HighlightedText");
    case QPalette::Link:
        return QString("Link");
    case QPalette::LinkVisited:
        return QString("LinkVisited");
    default:
        return QString("NoRole");
    }

}

bool KCColorConfigure::isValidColor(const Color &color)
{
    const int &r=color.r,&g=color.g,&b=color.b;
    if(r<0 || r>255 ||
       g<0 || g>255 ||
       b<0 || b>255)
    {
        return false;
    }

    return true;
}

void KCColorConfigure::readConfigure()
{
    QSettings settings(qApp->applicationDirPath() + "/" + colorConfigFilePath,QSettings::IniFormat);

    //ColorSheet part
    QStringList colorNames;
    settings.beginGroup("ColorSheet");
    colorNames=settings.childKeys();
    for(int i=0; i<colorNames.size(); i++)
    {
        Color color=parseColor(settings.value(colorNames.at(i)).toString());
        if(isValidColor(color))
        {
            colorSheet[colorNames.at(i)]=color;
        }
        else
        {
            qDebug()<<"KCColorConfigure: Error occured when parse "
                    <<colorConfigFilePath
                    <<" : "<<colorNames.at(i);
        }
    }
    settings.endGroup();


    //objects part
    QStringList objects=settings.childGroups();
    objects.removeAll("ColorSheet");
    for(int i=0; i<objects.size(); i++)
    {
        settings.beginGroup(objects.at(i));

        QStringList items=settings.childKeys();
        QVector<ColorInfo> colorInfos;
        for(int j=0; j<items.size(); j++)
        {
            ColorInfo _colorInfo;
            _colorInfo.colorRole=getColorRoleFromString(items.at(j));
            Color _color=parseObjectColor(settings.value(items.at(j)).toString());
            if(isValidColor(_color))
            {
                _colorInfo.color=_color;
                colorInfos<<_colorInfo;
            }
            else
            {
                qDebug()<<"KCColorConfigure: Error occured when parse "
                        <<colorConfigFilePath
                        <<" : "<<objects.at(i)<<" "<<items.at(j);
            }
        }
        colorInfoMap[objects.at(i)]=colorInfos;

        settings.endGroup();
    }
}

void KCColorConfigure::writeConfigure()
{
    QSettings settings(colorConfigFilePath,QSettings::IniFormat);

    settings.beginGroup("ColorSheet");
    for(auto i=colorSheet.begin();
        i!=colorSheet.end();
        i++)
    {
        Color _color=i.value();
        QString expression=QString("").sprintf("#%02x%02x%02x",_color.r,_color.g,_color.b);
        settings.setValue(i.key(), expression);
    }
    settings.endGroup();

    for(auto i=colorInfoMap.begin();
        i!=colorInfoMap.end();
        i++)
    {
        settings.beginGroup(i.key());

        const QVector<ColorInfo> &_colorInfos=i.value();
        for(auto j=_colorInfos.begin();
            j!=_colorInfos.end();
            j++)
        {
            const ColorInfo &_colorInfo=*j;
            const Color &_color=_colorInfo.color;
            QString expression=QString("").sprintf("#%02x%02x%02x",_color.r,_color.g,_color.b);
            settings.setValue(getColorRoleString(_colorInfo.colorRole), expression);
        }

        settings.endGroup();
    }
}

void KCColorConfigure::getPalette(QPalette &pal, const QString &objectName) const
{
    auto iterator=colorInfoMap.find(objectName);
    if(iterator!=colorInfoMap.end())
    {
        const QVector<ColorInfo> &colorVector=*iterator;
        for(auto i=colorVector.begin();
            i!=colorVector.end();
            i++)
        {
            pal.setColor(i->colorRole,QColor(i->color.r,i->color.g,i->color.b));
        }
    }
}

void KCColorConfigure::registerColorInfo(QPalette::ColorRole role,
        const QColor &color,
        const QString &objectName)
{
    QVector<ColorInfo> &colorInfos=this->colorInfoMap[objectName];
    ColorInfo colorInfo;
    color.getRgb(&colorInfo.color.r,&colorInfo.color.g,&colorInfo.color.b);
    colorInfo.colorRole=role;
    colorInfos.append(colorInfo);
}

KCColorConfigure::KCColorConfigure()
{

}

QString KCColorConfigure::getColorConfigFilePath()
{
    return colorConfigFilePath;
}

void KCColorConfigure::setColorConfigFilePath(const QString &filePath)
{
    colorConfigFilePath = filePath;
}
