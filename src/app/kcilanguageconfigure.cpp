#include "kcilanguageconfigure.h"

kciLanguageConfigure* kciLanguageConfigure::instance=nullptr;

kciLanguageConfigure* kciLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new kciLanguageConfigure:instance;
}

kciLanguageConfigure::kciLanguageConfigure()
{
    loadLanguageList();
}

void kciLanguageConfigure::readConfigure()
{

}

void kciLanguageConfigure::writeConfigure()
{

}

void kciLanguageConfigure::loadLanguageList()
{
    //Initialize Application Languages.
    QStringList filter;
    QDir *dir=new QDir(QString(qApp->applicationDirPath() + "/Locale/"));
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));
    for (QList<QFileInfo>::iterator i=list->begin();
         i!=list->end();
         ++i)
    {
        if(i->fileName().length() < 4)
        {
            continue;
        }

    }
}
