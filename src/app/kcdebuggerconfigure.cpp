#include "kcdebuggerconfigure.h"

KCDebuggerConfigure *KCDebuggerConfigure::instance=nullptr;

KCDebuggerConfigure *KCDebuggerConfigure::getInstance()
{
    return instance==nullptr?instance=new KCDebuggerConfigure:instance;
}

KCDebuggerConfigure::KCDebuggerConfigure()
{
}

void KCDebuggerConfigure::readConfigure()
{

}

void KCDebuggerConfigure::writeConfigure()
{

}
