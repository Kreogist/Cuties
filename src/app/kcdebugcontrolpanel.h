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

#ifndef KCDEBUGCONTROLBUTTONS_H
#define KCDEBUGCONTROLBUTTONS_H

#include <QDockWidget>

class QToolBar;
class QToolButton;

class KCDebugControlPanel : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugControlPanel(QWidget *parent = 0);

signals:

public slots:

private:
    enum debugContolButtons
    {
        debugStart,
        debugStop,
        debugRunToCursor,
        debugControlButtonCount
    };

    enum debugCursorControlButtons
    {
        debugNextLine,
        debugContinue,
        debugIntoFunction,
        debugNextInstruction,
        debugIntoInstruction,
        debugSkipFunction,
        debugCursorControlButtonCount
    };

    QToolBar *toolBar;
    QToolButton *debugControlButton[debugControlButtonCount];
    QToolButton *debugCursorControlButton[debugCursorControlButtonCount];
};

#endif // KCDEBUGCONTROLBUTTONS_H
