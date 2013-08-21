#ifndef KCIGENERALCONFIGURE_H
#define KCIGENERALCONFIGURE_H

#include "kciconfigure.h"

class kciGeneralConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciGeneralConfigure* getInstance();

private:
    kciGeneralConfigure();
    static kciGeneralConfigure* instance;
};
#endif // KCIGENERALCONFIGURE_H
