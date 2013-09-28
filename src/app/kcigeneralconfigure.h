#ifndef KCIGENERALCONFIGURE_H
#define KCIGENERALCONFIGURE_H

#include <QString>

#include "kciconfigure.h"

class kciGeneralConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciGeneralConfigure* getInstance();

    int getDefaultLanguageMode() const;
    QString getDefaultLanguageModeString();
    void setDefaultLanguageMode(const int &value);

    bool getRememberUnclosedFile() const;
    void setRememberUnclosedFile(bool value);

    bool getUseDefaultLanguageWhenOpen() const;
    void setUseDefaultLanguageWhenOpen(bool value);

    bool getUseDefaultLanguageWhenSave() const;
    void setUseDefaultLanguageWhenSave(bool value);

    QString getStrFileFilter() const;
    void setStrFileFilter(const QString &value);

    QString getAsfFilter() const;
    void setAsfFilter(const QString &value);

    QString getPtfFilter() const;
    void setPtfFilter(const QString &value);

    QString getHfFilter() const;
    void setHfFilter(const QString &value);

    QString getCfFilter() const;
    void setCfFilter(const QString &value);

    QString getCppfFilter() const;
    void setCppfFilter(const QString &value);

    QString getPasfFilter() const;
    void setPasfFilter(const QString &value);

    QString getAfFilter() const;
    void setAfFilter(const QString &value);

private:
    kciGeneralConfigure();
    int defaultLanguageMode;
    bool rememberUnclosedFile;
    bool useDefaultLanguageWhenOpen;
    bool useDefaultLanguageWhenSave;
    static kciGeneralConfigure* instance;

    QString strFileFilter;
    QString asfFilter, ptfFilter, hfFilter, cfFilter, cppfFilter, pasfFilter, afFilter;
};
#endif // KCIGENERALCONFIGURE_H
