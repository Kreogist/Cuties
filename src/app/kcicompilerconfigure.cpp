#include "kcicompilerconfigure.h"

kciCompilerConfigure* kciCompilerConfigure::instance=nullptr;

kciCompilerConfigure* kciCompilerConfigure::getInstance()
{
    return instance==nullptr?instance=new kciCompilerConfigure:instance;
}

kciCompilerConfigure::kciCompilerConfigure()
{
#ifdef Q_OS_UNIX
    gccPath="/usr/bin/gcc";
    gppPath="/usr/bin/g++";
    fpcPath="/usr/bin/fpc";
#endif

#ifdef Q_OS_WIN32
    gccPath="/MinGW/bin/gcc.exe";
    gppPath="/MinGW/bin/g++.exe";
    fpcPath="/fpc/fpc.exe";
#endif
}

void kciCompilerConfigure::readConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Compiler");
    gccPath=cfgOperator.value("GCC-Path", gccPath).toString();
    gppPath=cfgOperator.value("GPP-Path", gppPath).toString();
    fpcPath=cfgOperator.value("FPC-Path", fpcPath).toString();
    cfgOperator.endGroup();
}

void kciCompilerConfigure::writeConfigure()
{
    QSettings cfgOperator(getCfgFileName(), QSettings::IniFormat);
    cfgOperator.beginGroup("Compiler");
    cfgOperator.setValue("GCC-Path", gccPath);
    cfgOperator.setValue("GPP-Path", gppPath);
    cfgOperator.setValue("FPC-Path", fpcPath);
    cfgOperator.endGroup();
}

QString kciCompilerConfigure::getGccPath() const
{
#ifdef Q_OS_WIN32
    if(gccPath.mid(2,1)==":")
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

void kciCompilerConfigure::setGccPath(const QString &value)
{
    gccPath = value;
}

QString kciCompilerConfigure::getGppPath() const
{
#ifdef Q_OS_WIN32
    if(gppPath.mid(2,1)==":")
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

void kciCompilerConfigure::setGppPath(const QString &value)
{
    gppPath = value;
}

QString kciCompilerConfigure::getFpcPath() const
{
#ifdef Q_OS_WIN32
    if(fpcPath.mid(2,1)==":")
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

void kciCompilerConfigure::setFpcPath(const QString &value)
{
    fpcPath = value;
}
