
#ifndef KCIEDITORCONFIGURE_H
#define KCIEDITORCONFIGURE_H

#include "kciconfigure.h"

class kciEditorConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciEditorConfigure* getInstance();
    bool usingBlankInsteadTab() const;
    void setUsingBlankInsteadTab(bool enabled);
    int getTabWidth() const;
    void setTabWidth(const int& width);

private:
    kciEditorConfigure();
    static kciEditorConfigure* instance;
    bool isUsingBlankInsteadTab;
    int tabWidth;
};


#endif // KCIEDITORCONFIGURE_H
