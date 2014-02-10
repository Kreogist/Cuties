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

#include "kcfontconfigure.h"

#include <QDir>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QApplication>
#include <QFontDatabase>
#include <QMessageBox>

#include "kcmessagebox.h"

KCFontConfigure *KCFontConfigure::instance=nullptr;

KCFontConfigure *KCFontConfigure::getInstance()
{
    return instance==nullptr?instance=new KCFontConfigure:instance;
}

QString KCFontConfigure::getGroupName() const
{
    return "Font";
}

KCFontConfigure::KCFontConfigure()
{
    //Initalize Default Font
    initCustomFonts();

    readConfigure();

    applyConfigure();
}

QString KCFontConfigure::getFontName(const QString &key) const
{
    return getValue(key+"Font").toString();
}

void KCFontConfigure::setFontName(const QString &key, const QString &value)
{
    setValue(key+"Font",value);
    fonts[key].setFamily(value);
}

QFont KCFontConfigure::getFont(const QString &key)
{
    auto iterator=fonts.find(key);
    if(Q_UNLIKELY(iterator == fonts.end()))
    {
        QFont font(getValue(key+"Font").toString());
        font.setPixelSize(getValue(key+"FontSize").toInt());
        font.setStyleStrategy(QFont::PreferAntialias);
        fonts[key]=font;
    }

    return fonts[key];
}

void KCFontConfigure::setFont(const QString &key, const QFont &value)
{
    fonts[key]=value;
    setValue(key+"Font",value.family());
    setValue(key+"FontSize",value.pixelSize());
}

void KCFontConfigure::applyConfigure()
{
    setApplicationFont();
}

void KCFontConfigure::setApplicationFont()
{
    qApp->setFont(getFont("application"));
}

void KCFontConfigure::initCustomFonts()
{
    QStringList filter;
    QDir *dir=new QDir(QString(qApp->applicationDirPath() + "/Fonts/"));
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));

    int fontID(-1);
    bool fontWarningShown(false);
    for(QList<QFileInfo>::iterator i=list->begin();
        i!=list->end();
        ++i)
    {
        if(i->fileName().length() < 4)
        {
            continue;
        }
        QFile res(i->filePath());
        if(res.open(QIODevice::ReadOnly) == false)
        {
            if(fontWarningShown == false)
            {
                QMessageBox::warning(0,
                                     QApplication::applicationName(),
                                     QString(QApplication::tr("Error occur when load font file.")) +
                                     "\n" +
                                     QString(QApplication::tr("Error: ")) +
                                     res.errorString());
                fontWarningShown = true;
            }
        }
        else
        {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if(fontID == -1 && fontWarningShown == false)
            {
                QMessageBox::warning(0,
                                     QApplication::applicationName(),
                                     QString(QApplication::tr("Error occur when load font file.")) +
                                     "\n" +
                                     QString(QApplication::tr("Error: ")) +
                                     res.errorString());
                fontWarningShown = true;
            }
        }
    }
}

