#ifndef KCIDEBUGGERCONFIGURE_H
#define KCIDEBUGGERCONFIGURE_H

#include "kciconfigure.h"

class kciDebuggerConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciDebuggerConfigure *getInstance();

private:
    kciDebuggerConfigure();
    static kciDebuggerConfigure *instance;
};

#endif // KCIDEBUGGERCONFIGURE_H
