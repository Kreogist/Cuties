#include "kcigeneralconfigure.h"

kciGeneralConfigure* kciGeneralConfigure::instance=nullptr;

kciGeneralConfigure* kciGeneralConfigure::getInstance()
{
    return instance==nullptr?instance=new kciGeneralConfigure:instance;
}

kciGeneralConfigure::kciGeneralConfigure()
{
    defaultLanguageMode="cpp";
    rememberUnclosedFile=true;
}

void kciGeneralConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    defaultLanguageMode=settings.value("DefaultLanguageMode",
                                       defaultLanguageMode).toString();
    rememberUnclosedFile=settings.value("RememberUnclosed",
                                        rememberUnclosedFile).toBool();
    settings.endGroup();
}

void kciGeneralConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    settings.setValue("DefaultLanguageMode",defaultLanguageMode);
    settings.setValue("RememberUnclosed", rememberUnclosedFile);
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

bool kciGeneralConfigure::getRememberUnclosedFile() const
{
    return rememberUnclosedFile;
}

void kciGeneralConfigure::setRememberUnclosedFile(bool value)
{
    rememberUnclosedFile = value;
}
