#include "kclanguageconfigure.h"

KCLanguageConfigure *KCLanguageConfigure::instance=nullptr;

KCLanguageConfigure *KCLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new KCLanguageConfigure:instance;
}

KCLanguageConfigure::KCLanguageConfigure()
{
    //Set default settings.
    localeFileDir=qApp->applicationDirPath() + "/Locale/";
    localeTranslation=localeFileDir+"Locale.db";
    //Load Language File List.
    loadLanguageList();
    //Set Default Language.
    QLocale::setDefault(QLocale(QLocale::system().language(), QLocale::system().country()));
    //Get system default language name.
    defaultLanguageName=getLanguageString(QLocale::system().language());
    setLanguage(defaultLanguageName);
}

void KCLanguageConfigure::readConfigure()
{
    QString configLanguageName;
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    configLanguageName=settings.value("Language",
                                      currentLanguageName).toString();
    setLanguage(currentLanguageName);
    settings.endGroup();
}

void KCLanguageConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    settings.setValue("Language", currentLanguageName);
    settings.endGroup();
}

bool KCLanguageConfigure::setLanguage(const QString &newLanguageName)
{
    int newLanguageIndex=languageName.indexOf(newLanguageName);
    newLanguageIndex=newLanguageIndex==-1?0:newLanguageIndex;
    return setLanguageIndex(newLanguageIndex);
}

bool KCLanguageConfigure::setLanguageIndex(int newLanguageIndex)
{
    currentLanguageIndex=newLanguageIndex;
    currentLanguageName=languageName.at(currentLanguageIndex);
    return applyLangaugeSet(currentLanguageIndex);
}

bool KCLanguageConfigure::applyLangaugeSet(int languageIndex)
{
    qApp->removeTranslator(&appTrans);
    appTrans.load(languageFileList.at(languageIndex));
    bool installStatus=qApp->installTranslator(&appTrans);
    if(installStatus)
    {
        emit newLanguageSet();
    }
    return installStatus;
}

QStringList KCLanguageConfigure::getLanguageCaption() const
{
    return languageCaption;
}

QList<QPixmap> KCLanguageConfigure::getLanguageFileIcon() const
{
    return languageFileIcon;
}

QString KCLanguageConfigure::getLocaleFileDir() const
{
    return localeFileDir;
}

QStringList KCLanguageConfigure::getLanguageList() const
{
    return languageFileList;
}

QStringList KCLanguageConfigure::getLanguageNameList() const
{
    return languageName;
}

int KCLanguageConfigure::getCurrentLanguageIndex() const
{
    return currentLanguageIndex;
}

QString KCLanguageConfigure::getCurrentLanguageName() const
{
    return currentLanguageName;
}

QPixmap KCLanguageConfigure::getCurrentLanguageIcon() const
{
    return languageFileIcon.at(currentLanguageIndex);
}

QString KCLanguageConfigure::getLanguageString(QLocale::Language language)
{
    if(language==QLocale::Chinese)
    {
        if(QLocale::system().country()==QLocale::China)
        {
            return QString("SimplifiedChinese");
        }
        return QString("TraditionalChinese");
    }
    return QLocale::languageToString(language);
}

void KCLanguageConfigure::loadLanguageList()
{
    //Initialize Application Languages.
    //Clear current list
    languageName.clear();
    languageCaption.clear();
    languageFileList.clear();
    languageFileIcon.clear();

    //Search all qm language file
    QString localeFileName, localeName, localeIconFileName;
    QStringList filter;
    QSettings languageNameTranslate(localeTranslation, QSettings::IniFormat);
    QDir *dir=new QDir(localeFileDir);
    QFile localeIcon;
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));
    languageNameTranslate.beginGroup("Languages");
    for(QList<QFileInfo>::iterator i=list->begin();
        i!=list->end();
        ++i)
    {
        localeFileName=i->fileName();
        if(localeFileName.length() < 4)
        {
            continue;
        }
        //Load qm file to language list
        if(localeFileName.right(3)==QString(".qm"))
        {
            languageFileList.append(i->filePath());
            localeName=localeFileName.left(localeFileName.length()-3);
            languageName.append(localeName);
            languageCaption.append(languageNameTranslate.value(localeName,
                                                               localeName).toString());
            localeIconFileName=localeFileDir+localeName+".png";
            localeIcon.setFileName(localeIconFileName);
            if(localeIcon.exists())
            {
                languageFileIcon.append(QPixmap(localeIconFileName));
            }
            else
            {
                //TODO: Here should be replace by no icon
                languageFileIcon.append(QPixmap(localeIconFileName));
            }
        }
    }
    languageNameTranslate.endGroup();
}
