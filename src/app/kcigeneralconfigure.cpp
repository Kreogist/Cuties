#include "kcigeneralconfigure.h"

kciGeneralConfigure* kciGeneralConfigure::instance=nullptr;

kciGeneralConfigure* kciGeneralConfigure::getInstance()
{
    return instance==nullptr?instance=new kciGeneralConfigure:instance;
}

kciGeneralConfigure::kciGeneralConfigure()
{
    defaultLanguageMode=1;
    rememberUnclosedFile=true;
    useDefaultLanguageWhenOpen=false;
    useDefaultLanguageWhenSave=true;

    asfFilter = QObject::tr("All Support Files")+
            "(*.txt *.h *.hpp *.rh *.hh *.c *.cpp *.cc *.cxx *.c++ *.cp *.pas)";
    ptfFilter = QObject::tr("Plain Text Files")+"(*.txt)";
    hfFilter = QObject::tr("Hearder Files")+"(*.h *.hpp *.rh *.hh)";
    cfFilter = QObject::tr("C Source Files")+"(*.c)";
    cppfFilter = QObject::tr("C++ Source Files")+"(*.cpp *.cc *.cxx *.c++ *.cp)";
    pasfFilter = QObject::tr("Pascal Source Files")+"(*.pas)";
    afFilter = QObject::tr("All Files")+"(*.*)";

    strFileFilter = asfFilter + ";;" +
                    ptfFilter + ";;" +
                    hfFilter + ";;" +
                    cfFilter + ";;" +
                    cppfFilter + ";;" +
                    pasfFilter + ";;" +
                    afFilter;
}

void kciGeneralConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    QString strDefaultLanguageMode=settings.value("DefaultLanguageMode",
                                                  "cpp").toString();
    if(strDefaultLanguageMode=="c")
    {
        defaultLanguageMode=1;
    }
    else if(strDefaultLanguageMode=="cpp")
    {
        defaultLanguageMode=2;
    }
    else if(strDefaultLanguageMode=="pas")
    {
        defaultLanguageMode=3;
    }
    else
    {
        defaultLanguageMode=0;
    }
    rememberUnclosedFile=settings.value("RememberUnclosed",
                                        rememberUnclosedFile).toBool();
    useDefaultLanguageWhenOpen=settings.value("UseDefaultLanguageModeWhenOpen",
                                              useDefaultLanguageWhenOpen).toBool();
    useDefaultLanguageWhenSave=settings.value("UseDefaultLanguageModeWhenSave",
                                              useDefaultLanguageWhenSave).toBool();
    settings.endGroup();
}

void kciGeneralConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    settings.setValue("DefaultLanguageMode",getDefaultLanguageModeString());
    settings.setValue("RememberUnclosed", rememberUnclosedFile);
    settings.setValue("UseDefaultLanguageModeWhenOpen", useDefaultLanguageWhenOpen);
    settings.setValue("UseDefaultLanguageModeWhenSave", useDefaultLanguageWhenSave);
    settings.endGroup();
}

int kciGeneralConfigure::getDefaultLanguageMode() const
{
    return defaultLanguageMode;
}

QString kciGeneralConfigure::getDefaultLanguageModeString()
{
    switch(defaultLanguageMode)
    {
    case 1:
        return QString("c");
    case 2:
        return QString("cpp");
    case 3:
        return QString("pas");
    default:
        return QString("txt");
    }
}

void kciGeneralConfigure::setDefaultLanguageMode(const int &value)
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

bool kciGeneralConfigure::getUseDefaultLanguageWhenSave() const
{
    return useDefaultLanguageWhenSave;
}

void kciGeneralConfigure::setUseDefaultLanguageWhenSave(bool value)
{
    useDefaultLanguageWhenSave = value;
}

bool kciGeneralConfigure::getUseDefaultLanguageWhenOpen() const
{
    return useDefaultLanguageWhenOpen;
}

void kciGeneralConfigure::setUseDefaultLanguageWhenOpen(bool value)
{
    useDefaultLanguageWhenOpen = value;
}

QString kciGeneralConfigure::getStrFileFilter() const
{
    return strFileFilter;
}

void kciGeneralConfigure::setStrFileFilter(const QString &value)
{
    strFileFilter = value;
}

QString kciGeneralConfigure::getAfFilter() const
{
    return afFilter;
}

void kciGeneralConfigure::setAfFilter(const QString &value)
{
    afFilter = value;
}

QString kciGeneralConfigure::getPasfFilter() const
{
    return pasfFilter;
}

void kciGeneralConfigure::setPasfFilter(const QString &value)
{
    pasfFilter = value;
}

QString kciGeneralConfigure::getCppfFilter() const
{
    return cppfFilter;
}

void kciGeneralConfigure::setCppfFilter(const QString &value)
{
    cppfFilter = value;
}

QString kciGeneralConfigure::getCfFilter() const
{
    return cfFilter;
}

void kciGeneralConfigure::setCfFilter(const QString &value)
{
    cfFilter = value;
}

QString kciGeneralConfigure::getHfFilter() const
{
    return hfFilter;
}

void kciGeneralConfigure::setHfFilter(const QString &value)
{
    hfFilter = value;
}

QString kciGeneralConfigure::getPtfFilter() const
{
    return ptfFilter;
}

void kciGeneralConfigure::setPtfFilter(const QString &value)
{
    ptfFilter = value;
}

QString kciGeneralConfigure::getAsfFilter() const
{
    return asfFilter;
}

void kciGeneralConfigure::setAsfFilter(const QString &value)
{
    asfFilter = value;
}
