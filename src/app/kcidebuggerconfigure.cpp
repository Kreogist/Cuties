#include "kcidebuggerconfigure.h"

kciDebuggerConfigure* kciDebuggerConfigure::instance=nullptr;

kciDebuggerConfigure* kciDebuggerConfigure::getInstance()
{
    return instance==nullptr?instance=new kciDebuggerConfigure:instance;
}

kciDebuggerConfigure::kciDebuggerConfigure()
{
}

void kciDebuggerConfigure::readConfigure()
{

}

void kciDebuggerConfigure::writeConfigure()
{

}
