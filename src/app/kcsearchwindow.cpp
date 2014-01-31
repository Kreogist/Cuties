/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QGraphicsDropShadowEffect>
#include "kccolorconfigure.h"

#include "kcsearchwindow.h"

static const int searchWindowFixedWidth=290;
static const int SearchBarOffset = 20;

KCSearchWindow::KCSearchWindow(QWidget *parent) :
    KCSearchWidget(parent)
{
    setObjectName("KCSearchWindow");
    //Set Search Details.
    setFixedSize(searchWindowFixedWidth, 38);

    QPalette pal=palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);

    QGridLayout *searchLayout=(QGridLayout *)layout();

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setObjectName("KCSearchWindowCloseButton");
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    searchLayout->addWidget(closeButton,0,searchLayout->columnCount());

    //Set Button Palette
    pal=closeButton->palette();
    KCColorConfigure::getInstance()->getPalette(pal,closeButton->objectName());
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(animeHide()));

    showAnime=new QPropertyAnimation(this, "geometry", this);
    showAnime->setEasingCurve(QEasingCurve::OutCubic);
    showAnime->setDuration(300);

    hideAnime=new QPropertyAnimation(this, "geometry", this);
    hideAnime->setDuration(300);
    hideAnime->setEasingCurve(QEasingCurve::OutCubic);
    connect(hideAnime, SIGNAL(finished()), this, SLOT(hide()));
}

void KCSearchWindow::animeShow()
{
    QRect animeEndPos=rect();
    animeEndPos.setX(parentWidget()->width()-width()-SearchBarOffset);
    QRect animeStartPos=animeEndPos;
    animeStartPos.setTop(-animeStartPos.height());
    showAnime->setStartValue(animeStartPos);
    showAnime->setEndValue(animeEndPos);
    restoreLastSearchText();
    show();
    showAnime->start();
}

void KCSearchWindow::animeHide()
{
    QRect animeStartPos=geometry();
    QRect animeEndPos=animeStartPos;
    animeEndPos.setTop(-animeStartPos.height() - 20);
    animeEndPos.setHeight(38);
    hideAnime->setStartValue(animeStartPos);
    hideAnime->setEndValue(animeEndPos);
    emit requireLostFocus();
    hideAnime->start();
}
