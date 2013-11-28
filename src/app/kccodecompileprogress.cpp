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

#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

#include "kccodecompileprogress.h"

KCCodeCompileProgress::KCCodeCompileProgress(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeCompileProgress");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QVBoxLayout *compileProgressLayout=new QVBoxLayout(this);
    compileProgressLayout->setContentsMargins(0,0,0,0);
    compileProgressLayout->setSpacing(0);
    setLayout(compileProgressLayout);

    compileProgressDisplay=new QProgressBar(this);
    compileProgressLayout->addWidget(compileProgressDisplay);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);
}
