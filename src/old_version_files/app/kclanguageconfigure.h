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

#ifndef KCLANGUAGECONFIGURE_H
#define KCLANGUAGECONFIGURE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QApplication>
#include <QPixmap>
#include <QStringList>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QMetaEnum>

#include "kcconfigure.h"

class KCLanguageConfigure : public KCConfigure
{
    Q_OBJECT
public:
    static KCLanguageConfigure *getInstance();

    QStringList getLanguageList() const;
    QStringList getLanguageCaption() const;
    QStringList getLanguageNameList() const;
    QList<QPixmap> getLanguageFileIcon() const;
    int getCurrentLanguageIndex() const;
    QString getCurrentLanguageName() const;
    QPixmap getCurrentLanguageIcon() const;
    QString getLanguageString(QLocale::Language language);
    QString getLocaleFileDir() const;

signals:
    void newLanguageSet();

public slots:
    void setLanguage(const QString &newLanguageName);
    void setLanguageIndex(int newLangaugeIndex);

protected:
    QString getGroupName() const;
    void readConfigureCustomSteps();

private:
    void applyLangaugeSet(int languageIndex);

    //Language file folder & language translation file
    QString localeFileDir, localeTranslation;

    //Cache list
    QStringList languageFileList, languageName, languageCaption;
    QList<QPixmap> languageFileIcon;

    QString defaultLanguageName;
    QString currentLanguageName;
    int currentLanguageIndex;

    KCLanguageConfigure();
    static KCLanguageConfigure *instance;

    void loadLanguageList();

    QTranslator appTrans;
};

#endif // KCLANGUAGECONFIGURE_H
