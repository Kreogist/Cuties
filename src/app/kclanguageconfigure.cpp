#include "kclanguageconfigure.h"

KCLanguageConfigure *KCLanguageConfigure::instance=nullptr;

KCLanguageConfigure *KCLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new KCLanguageConfigure:instance;
}

KCLanguageConfigure::KCLanguageConfigure()
{
    //Set default settings.
    languageFileDir=qApp->applicationDirPath() + "/Locale/";
    //Load Language File List.
    loadLanguageList();
    //Set Default Language.
    QLocale::setDefault(QLocale(QLocale::system().language(), QLocale::system().country()));
    currLanguageName=QLocale::system().name();
    setLanguage(currLanguageName);
}

void KCLanguageConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    currLanguageName=settings.value("Language",
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

void KCLanguageConfigure::setLanguage(QString newLanguageName)
{
    int languageID=languageName.indexOf(newLanguageName + ".qm");
    if(languageID != -1)
    {
        appTrans.load(languageFileList.at(languageID));
        qApp->installTranslator(&appTrans);
    }
}

QStringList KCLanguageConfigure::getLanguageList() const
{
    return languageFileList;
}

QStringList KCLanguageConfigure::getLanguageNameList() const
{
    return languageName;
}

void KCLanguageConfigure::loadLanguageList()
{
    //Initialize Application Languages.
    QString currFileName;
    QStringList filter;
    QDir *dir=new QDir(languageFileDir);
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
    }
}
