#include "kcilanguageconfigure.h"

kciLanguageConfigure* kciLanguageConfigure::instance=nullptr;

kciLanguageConfigure* kciLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new kciLanguageConfigure:instance;
}

kciLanguageConfigure::kciLanguageConfigure()
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

void kciLanguageConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    currLanguageName=settings.value("Language",
                                    currLanguageName).toString();
    settings.endGroup();
}

void kciLanguageConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Language");
    settings.setValue("Language", currLanguageName);
    settings.endGroup();
}

void kciLanguageConfigure::setLanguage(QString newLanguageName)
{
    appTrans.load(languageFileList.at(languageName.indexOf(newLanguageName + ".qm")));
    qApp->installTranslator(&appTrans);
}

QStringList kciLanguageConfigure::getLanguageList() const
{
    return languageFileList;
}

QStringList kciLanguageConfigure::getLanguageNameList() const
{
    return languageName;
}

void kciLanguageConfigure::loadLanguageList()
{
    //Initialize Application Languages.
    QString currFileName;
    QStringList filter;
    QDir *dir=new QDir(languageFileDir);
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));
    for (QList<QFileInfo>::iterator i=list->begin();
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
