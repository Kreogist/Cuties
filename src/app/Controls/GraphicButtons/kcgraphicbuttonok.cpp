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

#include "kcgraphicbuttonok.h"

KCGraphicButtonOK::KCGraphicButtonOK(QWidget *parent) :
    KCGraphicButtonBase(parent)
{
    setNormalGraphic(QPixmap(":/Buttons/image/Buttons/ok_normal.png"));
    setHoverGraphic(QPixmap(":/Buttons/image/Buttons/ok_hover.png"));
    setPressedGraphic(QPixmap(":/Buttons/image/Buttons/ok_normal.png"));
}
