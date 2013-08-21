#ifndef KCIFILEASSOCIATIONCONFIGURE_H
#define KCIFILEASSOCIATIONCONFIGURE_H

#include "kciconfigure.h"

class kciFileAssociationConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciFileAssociationConfigure* getInstance();

private:
    kciFileAssociationConfigure();
    static kciFileAssociationConfigure* instance;
};

#endif // KCIFILEASSOCIATIONCONFIGURE_H
