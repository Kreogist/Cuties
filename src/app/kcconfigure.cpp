#include "kcconfigure.h"

QString KCConfigure::cfgFileName;

QString KCConfigure::getCfgFileName()
{
    return cfgFileName;
}

void KCConfigure::setCfgFileName(const QString &value)
{
    cfgFileName = value;
}


