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
