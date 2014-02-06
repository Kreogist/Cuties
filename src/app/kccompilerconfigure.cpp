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

#include "kccompilerconfigure.h"

KCCompilerConfigure *KCCompilerConfigure::instance=nullptr;

KCCompilerConfigure *KCCompilerConfigure::getInstance()
{
    return instance==nullptr?instance=new KCCompilerConfigure:instance;
}

KCCompilerConfigure::KCCompilerConfigure()
{
#ifdef Q_OS_UNIX
    setValue("GPP-Path","/usr/bin/gcc");
    setValue("GCC-Path","/usr/bin/g++");
    setValue("FPC-Path","/usr/bin/fpc");
#endif

#ifdef Q_OS_WIN32
    setValue("GPP-Path","/Compilers/MinGW/bin/g++.exe");
    setValue("GCC-Path","/Compilers/MinGW/bin/gcc.exe");
    setValue("FPC-Path","/Compilers/FPC/bin/i386-win32/fpc.exe");
#endif

    setValue("delayCompile", false);
    setValue("delayTimeout", 20);
}

QString KCCompilerConfigure::getGroupName()
{
    return "Compiler";
}
