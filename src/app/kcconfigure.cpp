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

#include "kcconfigure.h"

QString KCConfigure::cfgFileName;

QString KCConfigure::getCfgFileName()
{
    return cfgFileName;
}

void KCConfigure::setCfgFileName(const QString &value)
{
    cfgFileName = value;
}

void KCConfigure::setGroupName(const QString &value)
{
    groupName = value;
}

void KCConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup(groupName);
    QStringList currentKeys=settings.childKeys();
    for(QStringList::const_iterator i=currentKeys.begin();
        i!=currentKeys.end();
        i++)
    {
        configureMap[*i]=settings.value(*i);
    }
    settings.endGroup();
}

void KCConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup(groupName);
    QList<QString> keys=configureMap.keys();
    for(QList<QString>::iterator i=keys.begin();
        i!=keys.end();
        i++)
    {
        settings.setValue(*i, configureMap[*i]);
    }
    settings.endGroup();
}

QVariant KCConfigure::getValue(const QString &key)
{
    return configureMap[key];
}

void KCConfigure::setValue(const QString &key, const QVariant &value)
{
    configureMap[key]=value;
}

void KCConfigure::setPathValue(const QString &key,
                                       const QString &value)
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

QString KCConfigure::getPathValue(const QString &key)
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
