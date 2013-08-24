#ifndef KCILANGUAGECONFIGURE_H
#define KCILANGUAGECONFIGURE_H

#include "kciconfigure.h"

class kciLanguageConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciLanguageConfigure* getInstance();

private:
    kciLanguageConfigure();
    static kciLanguageConfigure* instance;
};

#endif // KCILANGUAGECONFIGURE_H
