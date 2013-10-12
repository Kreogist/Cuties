#ifndef KCFILEASSOCIATION_H
#define KCFILEASSOCIATION_H

#include "kcconfigure.h"

class KCFileAssociationConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCFileAssociationConfigure *getInstance();

private:
    KCFileAssociationConfigure();
    static KCFileAssociationConfigure *instance;
};

#endif // KCFILEASSOCIATION_H
