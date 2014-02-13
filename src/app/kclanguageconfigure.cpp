/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QSettings>

#include "kclanguageconfigure.h"

KCLanguageConfigure *KCLanguageConfigure::instance=nullptr;

KCLanguageConfigure *KCLanguageConfigure::getInstance()
{
    return instance==nullptr?instance=new KCLanguageConfigure:instance;
}

QString KCLanguageConfigure::getGroupName() const
{
    return "Language";
}

void KCLanguageConfigure::readConfigureCustomSteps()
{
    currentLanguageName=getValue("Language").toString();
}

KCLanguageConfigure::KCLanguageConfigure()
{
    //Set default settings.
    currentLanguageIndex=-1;
    localeFileDir=qApp->applicationDirPath() + "/Locale/";
    localeTranslation=localeFileDir+"Locale.db";
    //Load Language File List.
    loadLanguageList();
    //Set Default Language.
    QLocale::setDefault(QLocale(QLocale::system().language(),
                                QLocale::system().country()));
    //Get system default language name.
    defaultLanguageName=getLanguageString(QLocale::system().language());
    setLanguage(defaultLanguageName);

    //try readconfigure
    readConfigure();
    if(!currentLanguageName.isEmpty())
        setLanguage(currentLanguageName);
}

void KCLanguageConfigure::setLanguage(const QString &newLanguageName)
{
    int newLanguageIndex=languageName.indexOf(newLanguageName);
    if(newLanguageIndex==-1)
    {
        qDebug()<<"Unknow language name: "<<newLanguageName;
        return;
    }
    setLanguageIndex(newLanguageIndex);
}

void KCLanguageConfigure::setLanguageIndex(int newLanguageIndex)
{
    currentLanguageIndex=newLanguageIndex;
    currentLanguageName=languageName.at(currentLanguageIndex);
    setValue("Language",currentLanguageName);
    writeConfigure();
    applyLangaugeSet(currentLanguageIndex);
}

void KCLanguageConfigure::applyLangaugeSet(int languageIndex)
{
    qApp->removeTranslator(&appTrans);
    qDebug()<<languageFileList.at(languageIndex);
    appTrans.load(languageFileList.at(languageIndex));
    qApp->installTranslator(&appTrans);
    emit newLanguageSet();
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
