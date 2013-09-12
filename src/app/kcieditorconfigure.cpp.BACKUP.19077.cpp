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

<<<<<<< HEAD
    settings.beginGroup("unClosedFilePaths");
    unClosedCurrent=settings.value("CurrIndex", -1).toInt();
    int i=settings.value("PathCount",0).toInt();
    QString numberString;
    while(i--)
    {
        numberString=QString::number(i);
        unClosedFilePaths.append(settings.value("f" + numberString).toString());
        unClosedFileH.append(settings.value("h" + numberString).toInt());
        unClosedFileV.append(settings.value("v" + numberString).toInt());
    }
    settings.endGroup();

=======
>>>>>>> aa3bff707487a2b0bea90da2a4b2f5ce4c4f0e91
    settings.endGroup();
}

void kciEditorConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    settings.setValue("TabWidth",tabWidth);
    settings.setValue("isUsingBlankInsteadTab",isUsingBlankInsteadTab);

<<<<<<< HEAD
    settings.beginGroup("unClosedFilePaths");
    settings.setValue("CurrIndex", unClosedCurrent);
    settings.setValue("PathCount",unClosedFilePaths.size());

    QString numberString;

    for(int i=0;i<unClosedFilePaths.size();i++)
    {
        numberString=QString::number(i);
        settings.setValue("f" + numberString,unClosedFilePaths.at(i));
        settings.setValue("v" + numberString, unClosedFileV.at(i));
        settings.setValue("h" + numberString, unClosedFileH.at(i));
    }
    settings.endGroup();

=======
>>>>>>> aa3bff707487a2b0bea90da2a4b2f5ce4c4f0e91
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
<<<<<<< HEAD
}

void kciEditorConfigure::clearAllUnClosedFilePaths()
{
    unClosedFilePaths.clear();
    unClosedFileH.clear();
    unClosedFileV.clear();
}

QList<QString> kciEditorConfigure::getAllUnClosedFilePaths() const
{
    return unClosedFilePaths;
}

QList<int> kciEditorConfigure::getAllUnClosedFileHs() const
{
    return unClosedFileH;
}

QList<int> kciEditorConfigure::getAllUnClosedFileVs() const
{
    return unClosedFileV;
}

void kciEditorConfigure::addUnClosedFilePath(const QString &path, const int &HValue, const int &VValue)
{
    unClosedFilePaths.append(path);
    unClosedFileH.append(HValue);
    unClosedFileV.append(VValue);
}

int kciEditorConfigure::getUnClosedCurrent() const
{
    return unClosedCurrent;
}

void kciEditorConfigure::setUnClosedCurrent(int value)
{
    unClosedCurrent = value;
=======

    emit tabWidthChanged(tabWidth);
>>>>>>> aa3bff707487a2b0bea90da2a4b2f5ce4c4f0e91
}
