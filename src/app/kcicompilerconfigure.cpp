#include "kcicompilerconfigure.h"

kciCompilerConfigure::kciCompilerConfigure()
{
#ifdef Q_OS_UNIX
    gccPath="/usr/bin/gcc";
    gppPath="/usr/bin/g++";
#endif

#ifdef Q_OS_WIN32
    gccPath="C:/MinGW/bin/gcc.exe";
    gppPath="C:/MinGW/bin/g++.exe";
#endif
}

void kciCompilerConfigure::readConfigure()
{

}

void kciCompilerConfigure::writeConfigure()
{

}
