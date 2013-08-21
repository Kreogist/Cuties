#ifndef KCIEDITORCONFIGURE_H
#define KCIEDITORCONFIGURE_H

#include "kciconfigure.h"

class kciEditorConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciEditorConfigure* getInstance();

private:
    kciEditorConfigure();
    static kciEditorConfigure* instance;
};


#endif // KCIEDITORCONFIGURE_H
