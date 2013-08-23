#include "kcigeneralconfigure.h"

kciGeneralConfigure* kciGeneralConfigure::instance=nullptr;

kciGeneralConfigure* kciGeneralConfigure::getInstance()
{
    return instance==nullptr?instance=new kciGeneralConfigure:instance;
}

kciGeneralConfigure::kciGeneralConfigure()
{
    defaultLanguageMode="cpp";
}

void kciGeneralConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    defaultLanguageMode=settings.value("Default Language Mode",
                                       defaultLanguageMode).toString();
    settings.endGroup();
}

void kciGeneralConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    settings.setValue("Default Language Mode",
                      defaultLanguageMode);
    settings.endGroup();
}

QString kciGeneralConfigure::getDefaultLanguageMode() const
{
    return defaultLanguageMode;
}

void kciGeneralConfigure::setDefaultLanguageMode(const QString &value)
{
    defaultLanguageMode = value;
}
