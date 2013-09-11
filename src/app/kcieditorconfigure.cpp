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

#include "kcieditorconfigure.h"

kciEditorConfigure* kciEditorConfigure::instance=nullptr;

kciEditorConfigure::kciEditorConfigure()
{
    isUsingBlankInsteadTab=true;
    tabWidth=4;
}

kciEditorConfigure* kciEditorConfigure::getInstance()
{
    return instance==nullptr?instance=new kciEditorConfigure:instance;
}

void kciEditorConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    tabWidth=settings.value("TabWidth",tabWidth).toInt();
    isUsingBlankInsteadTab=settings.value("isUsingBlankInsteadTab",
                                          isUsingBlankInsteadTab).toBool();

    settings.beginGroup("unClosedFilePaths");
    int i=settings.value("PathCount",0).toInt();
    while(i--)
        unClosedFilePaths.append(settings.value(QString::number(i)).toString());
    settings.endGroup();

    settings.endGroup();
}

void kciEditorConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    settings.setValue("TabWidth",tabWidth);
    settings.setValue("isUsingBlankInsteadTab",isUsingBlankInsteadTab);

    settings.beginGroup("unClosedFilePaths");
    settings.remove("");
    settings.setValue("PathCount",unClosedFilePaths.size());
    for(int i=0;i<unClosedFilePaths.size();i++)
        settings.setValue(QString::number(i),unClosedFilePaths.at(i));
    settings.endGroup();

    settings.endGroup();
}

bool kciEditorConfigure::usingBlankInsteadTab() const
{
    return isUsingBlankInsteadTab;
}

void kciEditorConfigure::setUsingBlankInsteadTab(bool enabled)
{
    isUsingBlankInsteadTab=enabled;
}

int kciEditorConfigure::getTabWidth() const
{
    return tabWidth;
}

void kciEditorConfigure::setTabWidth(const int &width)
{
    tabWidth=width;
}

void kciEditorConfigure::clearAllUnClosedFilePaths()
{
    unClosedFilePaths.clear();
}

QList<QString> kciEditorConfigure::getAllUnClosedFilePaths() const
{
    return unClosedFilePaths;
}

void kciEditorConfigure::addUnClosedFilePath(const QString &path)
{
    unClosedFilePaths.append(path);
}
