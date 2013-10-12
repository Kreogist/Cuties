#ifndef KCDEBUGGERCONFIGURE_H
#define KCDEBUGGERCONFIGURE_H

#include "kcconfigure.h"

class KCDebuggerConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCDebuggerConfigure *getInstance();

private:
    KCDebuggerConfigure();
    static KCDebuggerConfigure *instance;
};

#endif // KCDEBUGGERCONFIGURE_H
