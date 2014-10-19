#include "kcfileassociation.h"

KCFileAssociationConfigure *KCFileAssociationConfigure::instance=nullptr;

KCFileAssociationConfigure *KCFileAssociationConfigure::getInstance()
{
    return instance==nullptr?instance=new KCFileAssociationConfigure:instance;
}

KCFileAssociationConfigure::KCFileAssociationConfigure()
{
    readConfigure();
}

QString KCFileAssociationConfigure::getGroupName() const
{
    return "FileAssociation";
}
