#ifndef KCICOMPILERCONFIGURE_H
#define KCICOMPILERCONFIGURE_H

#include <QString>

#include "kciconfigure.h"

class kciCompilerConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciCompilerConfigure* getInstance();

private:
    kciCompilerConfigure();
    static kciCompilerConfigure* instance;

    QString gccPath, gppPath, fpcPath;
};

#endif // KCICOMPILERCONFIGURE_H
