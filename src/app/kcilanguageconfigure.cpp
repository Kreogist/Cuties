#include "kcilanguageconfigure.h"

kciLanguageConfigure* kciLanguageConfigure::instance=nullptr;

kciLanguageConfigure* kciLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new kciLanguageConfigure:instance;
}

kciLanguageConfigure::kciLanguageConfigure()
{
}

void kciLanguageConfigure::readConfigure()
{

}

void kciLanguageConfigure::writeConfigure()
{

}
