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
#include <QStyle>
#include <QProcess>
#include <QDebug>

#include "kcgeneralconfigure.h"
#include "kceditorconfigure.h"
#include "kccompilerconfigure.h"
#include "kcdebuggerconfigure.h"
#include "kcfileassociation.h"
#include "kclanguageconfigure.h"
#include "kchistoryconfigure.h"
#include "kccolorconfigure.h"
#include "kcfontconfigure.h"

#include "kcglobal.h"

KCGlobal *KCGlobal::instance=nullptr;

KCGlobal::KCGlobal()
{
    settingsFileName=QString("Settings/Cuties.ini");
    KCConfigure::setCfgFileName(settingsFileName);

    cfgConfiger.append(KCGeneralConfigure::getInstance());
    cfgConfiger.append(KCEditorConfigure::getInstance());
    cfgConfiger.append(KCCompilerConfigure::getInstance());
    cfgConfiger.append(KCDebuggerConfigure::getInstance());
    cfgConfiger.append(KCFileAssociationConfigure::getInstance());
    cfgConfiger.append(KCLanguageConfigure::getInstance());
    cfgConfiger.append(KCHistoryConfigure::getInstance());
    cfgConfiger.append(KCColorConfigure::getInstance());
    cfgConfiger.append(KCFontConfigure::getInstance());
}

void KCGlobal::readSettings()
{
    for(int i=0; i<cfgConfiger.size(); i++)
    {
        cfgConfiger.at(i)->readConfigure();
    }
}

void KCGlobal::writeSettings()
{
    for(int i=0; i<cfgConfiger.size(); i++)
    {
        cfgConfiger.at(i)->writeConfigure();
    }
}

void KCGlobal::setSettingsFileName(const QString &filePath)
{
    settingsFileName=filePath;
}

QString KCGlobal::getSettingsFileName() const
{
    return settingsFileName;
}

KCGlobal *KCGlobal::getInstance()
{
    return instance==nullptr?instance=new KCGlobal:instance;
}


void KCGlobal::showInGraphicalShell(const QString &filePath)
{
#ifdef Q_OS_WIN32
    QProcess::startDetached("explorer.exe",
                            QStringList(QString(QLatin1String("/select,") +
                                        QDir::toNativeSeparators(filePath))));
    return;
#endif
#ifdef Q_OS_MACX
    QStringList scriptArgs;
    scriptArgs << QLatin1String("-e")
               << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
                                     .arg(filePath);
    QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    scriptArgs.clear();
    scriptArgs << QLatin1String("-e")
               << QLatin1String("tell application \"Finder\" to activate");
    QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    return;
#endif
}
