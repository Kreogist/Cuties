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
    currLanguageName=QLocale::system().name();
    setLanguage(currLanguageName);
    qDebug()<<QLocale::scriptToString(QLocale::system().script());
}

void KCLanguageConfigure::readConfigure()
{
    QString configLanguageName;
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    configLanguageName=settings.value("Language",
                                      currLanguageName).toString();
    settings.endGroup();
}

void KCLanguageConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    settings.setValue("Language", currLanguageName);
    settings.endGroup();
}

int KCLanguageConfigure::setLanguage(QString newLanguageName)
{
    int languageIndex=languageName.indexOf(newLanguageName + ".qm");
    if(languageIndex != -1)
    {
        currLanguageIndex=languageIndex;
        applyLangaugeSet(currLanguageIndex);
    }
    return languageIndex;
}

void KCLanguageConfigure::setLanguageIndex(int newLanguageIndex)
{
    currLanguageIndex=newLanguageIndex;
    currLanguageName=languageName.at(currLanguageIndex);
    applyLangaugeSet(currLanguageIndex);
}

void KCLanguageConfigure::applyLangaugeSet(int languageIndex)
{
    qApp->removeTranslator(&appTrans);
    appTrans.load(languageFileList.at(languageIndex));
    qApp->installTranslator(&appTrans);
    emit newLanguageSet();
}

QStringList KCLanguageConfigure::getLanguageList() const
{
    return languageFileList;
}

QStringList KCLanguageConfigure::getLanguageNameList() const
{
    return languageName;
}

int KCLanguageConfigure::getCurrLanguageIndex() const
{
    return currLanguageIndex;
}

void KCLanguageConfigure::loadLanguageList()
{
    //Initialize Application Languages.
    //Load language translation

    /*
    QString currFileName;
    QStringList filter;
    QDir *dir=new QDir(localeFileDir);
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(QList<QFileInfo>::iterator i=list->begin();
        i!=list->end();
        ++i)
    {
        currFileName=i->fileName();
        if(currFileName.length() < 4)
        {
            continue;
        }
        if(currFileName.right(3)==QString(".qm"))
        {
            languageFileList.append(i->filePath());
            languageName.append(currFileName);
        }
    }*/
}
