#ifndef KCIGENERALCONFIGURE_H
#define KCIGENERALCONFIGURE_H

#include "kciconfigure.h"

class kciGeneralConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciGeneralConfigure* getInstance();

    QString getDefaultLanguageMode() const;
    void setDefaultLanguageMode(const QString &value);

private:
    kciGeneralConfigure();
    QString defaultLanguageMode;
    static kciGeneralConfigure* instance;
};
#endif // KCIGENERALCONFIGURE_H
