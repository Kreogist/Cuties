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

#ifndef KCEDITORCONFIGURE_H
#define KCEDITORCONFIGURE_H

#include <QList>
#include <QDebug>
#include <QTextOption>

#include "kcconfigure.h"

class KCEditorConfigure : public KCConfigure
{
    Q_OBJECT

public:
    void readConfigure();
    void writeConfigure();
    static KCEditorConfigure *getInstance();
    bool usingBlankInsteadTab() const;
    void setUsingBlankInsteadTab(bool enabled);
    int getTabWidth() const;
    void setTabWidth(const int &width);
    QTextOption::WrapMode getWrapMode() const;
    void setWrapMode(QTextOption::WrapMode value);
    int getCursorWidth() const;
    void setCursorWidth(int value);
    bool getOverwriteMode() const;
    void setOverwriteMode(bool value);
    bool getTabMoveable() const;
    void setTabMoveable(bool value);
    bool getTabCloseable() const;
    void setTabCloseable(bool value);
    bool getLineNumVisible() const;
    void setLineNumVisible(bool value);

signals:
    void tabWidthChanged(int newValue);
    void wrapModeChanged(QTextOption::WrapMode newWrapMode);
    void cursorWidthChanged(int newValue);
    void tabMoveableChanged(bool newValue);
    void tabCloseableChanged(bool newValue);
    void spaceInsteadOfTab(bool newValue);
    void lineNumPanelVisibleChanged(bool newValue);

private:
    KCEditorConfigure();
    static KCEditorConfigure *instance;

    //Values:
    QTextOption::WrapMode wrapMode;
    bool isUsingBlankInsteadTab, overwriteMode;
    bool lineNumVisible;
    int tabWidth, cursorWidth;
    bool tabMoveable, tabCloseable;
};


#endif // KCEDITORCONFIGURE_H
