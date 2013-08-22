#include "kcigeneralconfigure.h"

kciGeneralConfigure* kciGeneralConfigure::instance=nullptr;

kciGeneralConfigure* kciGeneralConfigure::getInstance()
{
    return instance==nullptr?instance=new kciGeneralConfigure:instance;
}

kciGeneralConfigure::kciGeneralConfigure()
{
}

void kciGeneralConfigure::readConfigure()
{

}

void kciGeneralConfigure::writeConfigure()
{

}
