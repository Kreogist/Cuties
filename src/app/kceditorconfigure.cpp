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

#include "kcclipboard.h"

#include "kceditorconfigure.h"

KCEditorConfigure *KCEditorConfigure::instance=nullptr;

KCEditorConfigure::KCEditorConfigure()
{
    setGroupName("Editor");
}

KCEditorConfigure *KCEditorConfigure::getInstance()
{
    return instance==nullptr?instance=new KCEditorConfigure:instance;
}

QTextOption::WrapMode KCEditorConfigure::indexToWrapMode(int index)
{
    switch(index)
    {
    case 0:
        return QTextOption::NoWrap;
    case 1:
        return QTextOption::WordWrap;
    case 2:
        return QTextOption::ManualWrap;
    case 3:
        return QTextOption::WrapAnywhere;
    case 4:
        return QTextOption::WrapAtWordBoundaryOrAnywhere;
    };
    return QTextOption::NoWrap;
}

void KCEditorConfigure::readConfigure()
{
    KCConfigure::readConfigure();
    KCClipboard::getInstance()->setMaxDataCount(
                getValue("ClipboardMax").toInt());
}

int KCEditorConfigure::getWrapModeNumber(QTextOption::WrapMode destinationWrapMode) const
{
    switch(destinationWrapMode)
    {
    case QTextOption::NoWrap:
    case QTextOption::ManualWrap:
        return 0;
    case QTextOption::WordWrap:
        return 1;
    case QTextOption::WrapAnywhere:
        return 2;
    case QTextOption::WrapAtWordBoundaryOrAnywhere:
        return 3;
    }
    return 0;
}

void KCEditorConfigure::writeConfigure()
{
    KCConfigure::writeConfigure();
    KCClipboard::getInstance()->setMaxDataCount(getValue("ClipboardMax").toInt());
    emit editorConfigureRefresh();
}
