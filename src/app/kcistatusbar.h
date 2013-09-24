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


#ifndef KCISTATUSBAR_H
#define KCISTATUSBAR_H

#include <QLabel>
#include <QDebug>
#include <QStatusBar>

//#include "kcifiletype.h"
#include "kcistatuscursorinfo.h"
#include "kcistatusrewriteinfo.h"

class kciStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    kciStatusBar(QWidget *parent);
    void showGotoBar(int currentValue, int MaxValue);

signals:
    void ToNewPosition(int NewLineNum);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);
    void updateRewriteMode(bool NewValue);
    void hideRewriteDisplay();

private:
    //kciFileType *kscFileTypeDisplay;
    kciStatusCursorInfo *kscCursorPosition;
    kciStatusRewriteInfo *lblRewriteMode;
};

#endif // KCISTATUSBAR_H
