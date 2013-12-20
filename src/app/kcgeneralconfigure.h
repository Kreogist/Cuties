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
    void readConfigure();
    void writeConfigure();
    static KCGeneralConfigure *getInstance();

    int getDefaultLanguageMode() const;
    QString getDefaultLanguageModeString();
    void setDefaultLanguageMode(const int &value);

    bool getRememberUnclosedFile() const;
    void setRememberUnclosedFile(bool value);

    bool getUseDefaultLanguageWhenOpen() const;
    void setUseDefaultLanguageWhenOpen(bool value);

    bool getUseDefaultLanguageWhenSave() const;
    void setUseDefaultLanguageWhenSave(bool value);

    QString getStrFileFilter() const;
    void setStrFileFilter(const QString &value);

    QString getAsfFilter() const;
    void setAsfFilter(const QString &value);

    QString getPtfFilter() const;
    void setPtfFilter(const QString &value);

    QString getHfFilter() const;
    void setHfFilter(const QString &value);

    QString getCfFilter() const;
    void setCfFilter(const QString &value);

    QString getCppfFilter() const;
    void setCppfFilter(const QString &value);

    QString getPasfFilter() const;
    void setPasfFilter(const QString &value);

    QString getAfFilter() const;
    void setAfFilter(const QString &value);

    int getSearchEngineIndex() const;
    void setSearchEngineIndex(int value);

    QList<searchEngine> getSearchEngineList() const;
    void setSearchEngineList(const QList<searchEngine> &value);


public slots:
    void retranslate();
    void retranslateAndSet();

private:
    KCGeneralConfigure();
    int defaultLanguageMode;
    bool rememberUnclosedFile;
    bool useDefaultLanguageWhenOpen;
    bool useDefaultLanguageWhenSave;
    static KCGeneralConfigure *instance;
    int searchEngineIndex;
    QList<searchEngine> searchEngineList;

    QString strFileFilter;
    QString asfFilter, ptfFilter, hfFilter, cfFilter, cppfFilter, pasfFilter, afFilter;
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
