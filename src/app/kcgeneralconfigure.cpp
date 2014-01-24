/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QStringList>

#include "kchistoryconfigure.h"

#include "kcgeneralconfigure.h"

KCGeneralConfigure *KCGeneralConfigure::instance=nullptr;

KCGeneralConfigure *KCGeneralConfigure::getInstance()
{
    return instance==nullptr?instance=new KCGeneralConfigure:instance;
}

KCGeneralConfigure::KCGeneralConfigure()
{
    retranslate();

    QString defaultSearchEngineURL[SearchEngineCount];
    defaultSearchEngineURL[Google]="https://www.google.com.hk/#newwindow=1&safe=strict&q=";
    defaultSearchEngineURL[Yahoo]="http://search.yahoo.com/search?toggle=1&cop=mss&ei=UTF-8&fr=yfp-t-900&p=";
    defaultSearchEngineURL[Bing]="http://cn.bing.com/search?form=MXBTDF&pc=MXBR&q=";
    defaultSearchEngineURL[Baidu]="http://www.baidu.com/s?wd=";

    for(int i=0; i<SearchEngineCount; i++)
    {
        searchEngine defaultEngineAddor;
        defaultEngineAddor.name=defaultSearchEngine[i];
        defaultEngineAddor.engineURL=defaultSearchEngineURL[i];
        searchEngineList.append(defaultEngineAddor);
    }

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCGeneralConfigure::retranslateAndSet);
}

QString KCGeneralConfigure::getTotalFileFilter() const
{
    return totalFileFilter;
}

void KCGeneralConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    QStringList currentKeys=settings.childKeys();
    for(QStringList::const_iterator i=currentKeys.begin();
        i!=currentKeys.end();
        i++)
    {
        configureMap[*i]=settings.value(*i);
    }
    settings.endGroup();
}

void KCGeneralConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("General");
    QList<QString> keys=configureMap.keys();
    for(QList<QString>::iterator i=keys.begin();
        i!=keys.end();
        i++)
    {
        settings.setValue(*i, configureMap[*i]);
    }
    settings.endGroup();
    KCHistoryConfigure::getInstance()->setMaxRecentFilesSize(
                getValue("MaxRecentFilesSize").toInt());
}

QString KCGeneralConfigure::getDefaultLanguageModeString()
{
    switch(getValue("DefaultLanguageMode").toInt())
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

QList<searchEngine> KCGeneralConfigure::getSearchEngineList() const
{
    return searchEngineList;
}

QString KCGeneralConfigure::getFilter(int fileTypeIndex) const
{
    return fileTypeFilters[fileTypeIndex];
}

void KCGeneralConfigure::retranslate()
{
    fileTypeFilters[allSupportFiles] = tr("All Support Files")+
                "(*.txt *.h *.hpp *.rh *.hh *.c *.cpp *.cc *.cxx *.c++ *.cp *.pas)";
    fileTypeFilters[plainTextFiles] = tr("Plain Text Files")+"(*.txt)";
    fileTypeFilters[headerFiles] = tr("Hearder Files")+"(*.h *.hpp *.rh *.hh)";
    fileTypeFilters[cFiles] = tr("C Source Files")+"(*.c)";
    fileTypeFilters[cppFiles] = tr("C++ Source Files")+"(*.cpp *.cc *.cxx *.c++ *.cp)";
    fileTypeFilters[pascalFiles] = tr("Pascal Source Files")+"(*.pas)";
    fileTypeFilters[allFiles] = tr("All Files")+"(*.*)";

    totalFileFilter = fileTypeFilters[allSupportFiles] + ";;" +
                 fileTypeFilters[plainTextFiles] + ";;" +
                 fileTypeFilters[headerFiles] + ";;" +
                 fileTypeFilters[cFiles] + ";;" +
                 fileTypeFilters[cppFiles] + ";;" +
                 fileTypeFilters[pascalFiles] + ";;" +
                 fileTypeFilters[allFiles];

    defaultSearchEngine[Google]=tr("Google");
    defaultSearchEngine[Yahoo]=tr("Yahoo!");
    defaultSearchEngine[Bing]=tr("Bing");
    defaultSearchEngine[Baidu]=tr("Baidu");
}

void KCGeneralConfigure::retranslateAndSet()
{
    retranslate();
    for(int i=0;i<SearchEngineCount;i++)
    {
        searchEngine translateEngine=searchEngineList.at(i);
        translateEngine.name=defaultSearchEngine[i];
        searchEngineList.removeAt(i);
        searchEngineList.insert(i, translateEngine);
    }
}
