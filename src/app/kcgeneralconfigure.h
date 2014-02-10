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

#ifndef KCGENERALCONFIGURE_H
#define KCGENERALCONFIGURE_H

#include <QString>
#include <QList>

#include "kcconfigure.h"
#include "kclanguageconfigure.h"

struct searchEngine
{
    QString name;
    QString engineURL;
};

class KCGeneralConfigure : public KCConfigure
{
    Q_OBJECT
public:
    static KCGeneralConfigure *getInstance();

    QString getDefaultLanguageModeString();
    QList<searchEngine> getSearchEngineList() const;
    enum filterType
    {
        allSupportFiles,
        plainTextFiles,
        headerFiles,
        cFiles,
        cppFiles,
        pascalFiles,
        allFiles,
        FilterTypeCount
    };
    QString getFilter(int fileTypeIndex) const;
    QString getTotalFileFilter() const;

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    QString getGroupName() const;
    void writeConfigureCustomSteps();

private:
    KCGeneralConfigure();
    static KCGeneralConfigure *instance;
    QList<searchEngine> searchEngineList;
    QString fileTypeFilters[FilterTypeCount];
    QString totalFileFilter;

    enum embeddedOnlineSearch
    {
        Google,
        Yahoo,
        Bing,
        Baidu,
        SearchEngineCount
    };
    QString defaultSearchEngine[SearchEngineCount];
};
#endif // KCGENERALCONFIGURE_H
