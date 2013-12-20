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

#include "kccompilerconfigure.h"

KCCompilerConfigure *KCCompilerConfigure::instance=nullptr;

KCCompilerConfigure *KCCompilerConfigure::getInstance()
{
    return instance==nullptr?instance=new KCCompilerConfigure:instance;
}

KCCompilerConfigure::KCCompilerConfigure()
{
#ifdef Q_OS_UNIX
    gccPath="/usr/bin/gcc";
    gppPath="/usr/bin/g++";
    fpcPath="/usr/bin/fpc";
#endif

#ifdef Q_OS_WIN32
    gccPath="/Compiler/MinGW/bin/gcc.exe";
    gppPath="/Compiler/MinGW/bin/g++.exe";
    fpcPath="/Compiler/FPC/bin/i386-win32/fpc.exe";
#endif
}

void KCCompilerConfigure::readConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Compiler");
    gccPath=cfgOperator.value("GCC-Path", gccPath).toString();
    gppPath=cfgOperator.value("GPP-Path", gppPath).toString();
    fpcPath=cfgOperator.value("FPC-Path", fpcPath).toString();
    cfgOperator.endGroup();
}

void KCCompilerConfigure::writeConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Compiler");
    cfgOperator.setValue("GCC-Path", gccPath);
    cfgOperator.setValue("GPP-Path", gppPath);
    cfgOperator.setValue("FPC-Path", fpcPath);
    cfgOperator.endGroup();
}

QString KCCompilerConfigure::getGccPath() const
{
#ifdef Q_OS_WIN32
    if(gccPath.mid(1,1)==":")
    {
        return gccPath;
    }
    else
    {
        return qApp->applicationDirPath() + gccPath;
    }
#else
    return gccPath;
#endif
}

void KCCompilerConfigure::setGccPath(const QString &value)
{
    if(value.left(qApp->applicationDirPath().length())==qApp->applicationDirPath())
    {
        gccPath = value.mid(qApp->applicationDirPath().length());
    }
    else
    {
        gccPath = value;
    }
}

QString KCCompilerConfigure::getGppPath() const
{
#ifdef Q_OS_WIN32
    if(gppPath.mid(1,1)==":")
    {
        return gppPath;
    }
    else
    {
        return qApp->applicationDirPath() + gppPath;
    }
#else
    return gppPath;
#endif
}

void KCCompilerConfigure::setGppPath(const QString &value)
{
    if(value.left(qApp->applicationDirPath().length())==qApp->applicationDirPath())
    {
        gppPath = value.mid(qApp->applicationDirPath().length());
    }
    else
    {
        gppPath = value;
    }
}

QString KCCompilerConfigure::getFpcPath() const
{
#ifdef Q_OS_WIN32
    if(fpcPath.mid(1,1)==":")
    {
        return fpcPath;
    }
    else
    {
        return qApp->applicationDirPath() + fpcPath;
    }
#else
    return fpcPath;
#endif
}

void KCCompilerConfigure::setFpcPath(const QString &value)
{
    if(value.left(qApp->applicationDirPath().length())==qApp->applicationDirPath())
    {
        fpcPath = value.mid(qApp->applicationDirPath().length());
    }
    else
    {
        fpcPath = value;
    }
}
