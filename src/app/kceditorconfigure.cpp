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

#include "kceditorconfigure.h"

KCEditorConfigure *KCEditorConfigure::instance=nullptr;

KCEditorConfigure::KCEditorConfigure()
{
    wrapMode=QTextOption::NoWrap;
    isUsingBlankInsteadTab=true;
    tabWidth=4;
    cursorWidth=1;
    overwriteMode=false;
    tabMoveable=true;
    tabCloseable=true;
}

KCEditorConfigure *KCEditorConfigure::getInstance()
{
    return instance==nullptr?instance=new KCEditorConfigure:instance;
}

void KCEditorConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    tabWidth=settings.value("TabWidth",tabWidth).toInt();
    isUsingBlankInsteadTab=settings.value("isUsingBlankInsteadTab",
                                          isUsingBlankInsteadTab).toBool();
    int wMode=settings.value("WordWrap", wrapMode).toInt();
    switch(wMode)
    {
    case 0:
        wrapMode=QTextOption::NoWrap;
        break;
    case 1:
        wrapMode=QTextOption::WordWrap;
        break;
    case 2:
        wrapMode=QTextOption::ManualWrap;
        break;
    case 3:
        wrapMode=QTextOption::WrapAnywhere;
        break;
    case 4:
        wrapMode=QTextOption::WrapAtWordBoundaryOrAnywhere;
        break;
    default:
        wrapMode=QTextOption::NoWrap;
        break;
    }
    cursorWidth=settings.value("CursorWidth", cursorWidth).toInt();
    overwriteMode=settings.value("OverwriteMode", overwriteMode).toBool();
    tabMoveable=settings.value("TabMoveable", tabMoveable).toBool();
    tabCloseable=settings.value("TabCloseable", tabCloseable).toBool();
    settings.endGroup();
}

void KCEditorConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    settings.setValue("WordWrap", wrapMode);
    settings.setValue("TabWidth",tabWidth);
    settings.setValue("CursorWidth", cursorWidth);
    settings.setValue("isUsingBlankInsteadTab",isUsingBlankInsteadTab);
    settings.setValue("OverwriteMode", overwriteMode);
    settings.setValue("TabMoveable", tabMoveable);
    settings.setValue("TabCloseable", tabCloseable);
    settings.endGroup();
}

bool KCEditorConfigure::usingBlankInsteadTab() const
{
    return isUsingBlankInsteadTab;
}

void KCEditorConfigure::setUsingBlankInsteadTab(bool enabled)
{
    isUsingBlankInsteadTab=enabled;
}

int KCEditorConfigure::getTabWidth() const
{
    return tabWidth;
}

void KCEditorConfigure::setTabWidth(const int &width)
{
    tabWidth=width;
    emit tabWidthChanged(tabWidth);
}

QTextOption::WrapMode KCEditorConfigure::getWrapMode() const
{
    return wrapMode;
}

void KCEditorConfigure::setWrapMode(QTextOption::WrapMode value)
{
    wrapMode = value;
    emit wrapModeChanged(value);
}

int KCEditorConfigure::getCursorWidth() const
{
    return cursorWidth;
}

void KCEditorConfigure::setCursorWidth(int value)
{
    cursorWidth = value;
    emit cursorWidthChanged(value);
}

bool KCEditorConfigure::getOverwriteMode() const
{
    return overwriteMode;
}

void KCEditorConfigure::setOverwriteMode(bool value)
{
    overwriteMode = value;
}

bool KCEditorConfigure::getTabMoveable() const
{
    return tabMoveable;
}

void KCEditorConfigure::setTabMoveable(bool value)
{
    tabMoveable = value;
    emit tabMoveableChanged(value);
}

bool KCEditorConfigure::getTabCloseable() const
{
    return tabCloseable;
}

void KCEditorConfigure::setTabCloseable(bool value)
{
    tabCloseable = value;
    emit tabCloseableChanged(value);
}
