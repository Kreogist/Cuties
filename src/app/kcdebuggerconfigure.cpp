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
    gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
    gdbPath="/Compiler/MinGW/bin/gdb.exe";
#endif
}

QString KCDebuggerConfigure::getGdbPath() const
{
#ifdef Q_OS_WIN32
    if(gdbPath.mid(1,1)==":")
    {
        return gdbPath;
    }
    else
    {
        return qApp->applicationDirPath() + gdbPath;
    }
#else
    return gdbPath;
#endif
}

void KCDebuggerConfigure::setGdbPath(const QString &value)
{
    if(value.left(qApp->applicationDirPath().length())==qApp->applicationDirPath())
    {
        gdbPath = value.mid(qApp->applicationDirPath().length());
    }
    else
    {
        gdbPath = value;
    }
}

void KCDebuggerConfigure::readConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Debugger");
    gdbPath=cfgOperator.value("GDBPath", gdbPath).toString();
    cfgOperator.endGroup();
}

void KCDebuggerConfigure::writeConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Debugger");
    cfgOperator.setValue("GDBPath", gdbPath);
    cfgOperator.endGroup();
}
