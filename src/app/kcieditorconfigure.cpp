#include "kcieditorconfigure.h"

kciEditorConfigure* kciEditorConfigure::instance=nullptr;

kciEditorConfigure::kciEditorConfigure()
{
}

kciEditorConfigure* kciEditorConfigure::getInstance()
{
    return instance==nullptr?instance=new kciEditorConfigure:instance;
}

void kciEditorConfigure::readConfigure()
{

}

void kciEditorConfigure::writeConfigure()
{

}
