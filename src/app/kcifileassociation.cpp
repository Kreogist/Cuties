#include "kcifileassociation.h"

kciFileAssociationConfigure *kciFileAssociationConfigure::instance=nullptr;

kciFileAssociationConfigure *kciFileAssociationConfigure::getInstance()
{
    return instance==nullptr?instance=new kciFileAssociationConfigure:instance;
}

kciFileAssociationConfigure::kciFileAssociationConfigure()
{
}

void kciFileAssociationConfigure::readConfigure()
{

}

void kciFileAssociationConfigure::writeConfigure()
{

}
