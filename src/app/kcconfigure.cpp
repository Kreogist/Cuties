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

#include <QApplication>
#include <QDebug>

#include "kcconfigure.h"

QString KCConfigure::cfgFileName;

KCConfigure::KCConfigure()
{
}

QString KCConfigure::getCfgFileName()
{
    return cfgFileName;
}

void KCConfigure::setCfgFileName(const QString &value)
{
    cfgFileName = value;
}

void KCConfigure::readConfigure()
{
    //load default config
#ifdef Q_OS_WIN32
    //Test.
    qDebug()<<"Default loaded.";
    readConfigure(":/DefaultSettings/default_settings/Cuties_Win32.ini");
#else
    readConfigure(":/DefaultSettings/default_settings/Cuties_Unix.ini");
#endif
    readConfigure(getCfgFileName());
}

void KCConfigure::readConfigure(const QString &filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup(getGroupName());
    QStringList currentKeys=settings.childKeys();
    for(QStringList::const_iterator i=currentKeys.begin();
        i!=currentKeys.end();
        i++)
    {
        configureMap[*i]=settings.value(*i,configureMap[*i]);
    }
    settings.endGroup();
}

void KCConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup(getGroupName());
    QList<QString> keys=configureMap.keys();
    for(QList<QString>::iterator i=keys.begin();
        i!=keys.end();
        i++)
    {
        settings.setValue(*i, configureMap[*i]);
    }
    settings.endGroup();
}

QVariant KCConfigure::getValue(const QString &key) const
{
    auto mapIterator=configureMap.find(key);
    if(Q_UNLIKELY(mapIterator==configureMap.end()))
    {
        qDebug()<<"KCConfigure: unknow key value: "<<getGroupName()<<key;
        return QVariant();
    }

    return mapIterator.value();
}

void KCConfigure::setValue(const QString &key, const QVariant &value)
{
    configureMap[key]=value;
}

void KCConfigure::setPathValue(const QString &key, const QString &value)
{
    QString recordValue;
    if(value.left(qApp->applicationDirPath().length())==qApp->applicationDirPath())
    {
        recordValue = value.mid(qApp->applicationDirPath().length());
    }
    else
    {
        recordValue = value;
    }
    setValue(key, recordValue);
}

QString KCConfigure::getPathValue(const QString &key) const
{
    QString pathValue=getValue(key).toString();
#ifdef Q_OS_WIN32
    if(pathValue.mid(1,1)==":" || pathValue.left(2)=="//")
    {
        return pathValue;
    }
    else
    {
        return qApp->applicationDirPath() + pathValue;
    }
#else
    return pathValue;
#endif
}
