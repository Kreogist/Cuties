#include "kciconfigure.h"

QString kciConfigure::cfgFileName;

QString kciConfigure::getCfgFileName()
{
    return cfgFileName;
}

void kciConfigure::setCfgFileName(const QString &value)
{
    cfgFileName = value;
}
