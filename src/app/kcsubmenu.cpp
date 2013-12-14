/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Project Nerve.
 *
 *    Kreogist Nerve is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *    Kreogist Nerve is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  Kreogist Nerve. If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcsubmenu.h"

KCSubMenu::KCSubMenu(QWidget *parent) :
    QMenu(parent)
{
    showAnimation=new QPropertyAnimation(this, "geometry", this);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void KCSubMenu::showEvent(QShowEvent *e)
{
    QRect endPosition=geometry();
    QRect startPostion=endPosition;
    startPostion.setHeight(0);
    startPostion.setTop(startPostion.top()+21);
    int endPositionHeight=endPosition.height();
    int endPositionTop=endPosition.top()-endPosition.height()/2+21;
    if(endPositionTop<0)
    {
        endPositionTop=0;
    }
    endPosition.setTop(endPositionTop);
    endPosition.setHeight(endPositionHeight);
    showAnimation->setStartValue(startPostion);
    showAnimation->setEndValue(endPosition);
    showAnimation->start();
    QMenu::showEvent(e);
}
