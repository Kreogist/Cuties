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

#include "kcdebuggerconfigure.h"

KCDebuggerConfigure *KCDebuggerConfigure::instance=nullptr;

KCDebuggerConfigure *KCDebuggerConfigure::getInstance()
{
    return instance==nullptr?instance=new KCDebuggerConfigure:instance;
}

KCDebuggerConfigure::KCDebuggerConfigure()
{
#ifdef Q_OS_UNIX
    setValue("GDBPath", "/usr/bin/gdb");
#endif

#ifdef Q_OS_WIN32
    setValue("GDBPath", "/Compiler/MinGW/bin/gdb.exe");
#endif
}

void KCDebuggerConfigure::setPathValue(const QString &key,
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

QString KCDebuggerConfigure::getPathValue(const QString &key)
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

void KCDebuggerConfigure::readConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Debugger");
    QStringList currentKeys=cfgOperator.childKeys();
    for(QStringList::const_iterator i=currentKeys.begin();
        i!=currentKeys.end();
        i++)
    {
        configureMap[*i]=cfgOperator.value(*i);
    }
    cfgOperator.endGroup();
}

void KCDebuggerConfigure::writeConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Debugger");
    QList<QString> keys=configureMap.keys();
    for(QList<QString>::iterator i=keys.begin();
        i!=keys.end();
        i++)
    {
        cfgOperator.setValue(*i, configureMap[*i]);
    }
    cfgOperator.endGroup();
}
