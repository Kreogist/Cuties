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
    gccPath="C:/MinGW/bin/gcc.exe";
    gppPath="C:/MinGW/bin/g++.exe";
    fpcPath="c:/fpc/fpc.exe";
#endif
}

void kciCompilerConfigure::readConfigure()
{

}

void kciCompilerConfigure::writeConfigure()
{

}

QString kciCompilerConfigure::getGccPath() const
{
    return gccPath;
}

void kciCompilerConfigure::setGccPath(const QString &value)
{
    gccPath = value;
}

QString kciCompilerConfigure::getGppPath() const
{
    return gppPath;
}

void kciCompilerConfigure::setGppPath(const QString &value)
{
    gppPath = value;
}

QString kciCompilerConfigure::getFpcPath() const
{
    return fpcPath;
}

void kciCompilerConfigure::setFpcPath(const QString &value)
{
    fpcPath = value;
}
