/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
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

#include "kciglobal.h"

kciGlobal* kciGlobal::instance=nullptr;

kciGlobal::kciGlobal()
{
    settingsFileName=QString("Cuties.ini");
    kciConfigure::setCfgFileName(settingsFileName);

    cfgConfiger.append(kciGeneralConfigure::getInstance());
    cfgConfiger.append(kciEditorConfigure::getInstance());
    cfgConfiger.append(kciCompilerConfigure::getInstance());
    cfgConfiger.append(kciDebuggerConfigure::getInstance());
    cfgConfiger.append(kciFileAssociationConfigure::getInstance());
    cfgConfiger.append(kciLanguageConfigure::getInstance());
}

void kciGlobal::readSettings()
{
    for(int i=0; i<cfgConfiger.size(); i++)
    {
        cfgConfiger.at(i)->readConfigure();
    }
}

void kciGlobal::writeSettings()
{
    for(int i=0; i<cfgConfiger.size(); i++)
    {
        cfgConfiger.at(i)->writeConfigure();
    }
}

void kciGlobal::setSettingsFileName(const QString& filePath)
{
    settingsFileName=filePath;
}

QString kciGlobal::getSettingsFileName() const
{
    return settingsFileName;
}

kciGlobal* kciGlobal::getInstance()
{
    return instance==nullptr?instance=new kciGlobal:instance;
}
