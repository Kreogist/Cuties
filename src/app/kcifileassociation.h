#ifndef KCIFILEASSOCIATION_H
#define KCIFILEASSOCIATION_H

#include "kciconfigure.h"

class kciFileAssociationConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciFileAssociationConfigure *getInstance();

private:
    kciFileAssociationConfigure();
    static kciFileAssociationConfigure *instance;
};

#endif // KCIFILEASSOCIATION_H
