/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  Kreogist Cuties. If not, see <http://www.gnu.org/licenses/>.
 */
#include <QDebug>
#include <QPainter>
#include <QHBoxLayout>
#include <QBitmap>

#include "kcsubmenu.h"

KCMenuIndicator::KCMenuIndicator(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setObjectName("KCMenuIndicator");
    setAutoFillBackground(true);
    setWindowFlags(Qt::ToolTip |
                   Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    indicatorPixmap=QPixmap(":/img/image/indicator.png");
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0,0,0,0));
    pal.setColor(QPalette::Window, QColor(0,0,0,0));
    pal.setColor(QPalette::WindowText, QColor(0,0,0,0));
    pal.setColor(QPalette::AlternateBase, QColor(0,0,0,0));
    pal.setColor(QPalette::ToolTipBase, QColor(255,255,255,0));
    pal.setColor(QPalette::ToolTipText, QColor(255,255,255,0));
    pal.setColor(QPalette::Button, QColor(255,255,255,0));
    pal.setColor(QPalette::ButtonText, QColor(255,255,255,0));
    setPalette(pal);

    QLabel *indicatorIcon=new QLabel(this);
    indicatorIcon->setPixmap(indicatorPixmap);

    setMask(indicatorPixmap.mask());
    setFixedSize(28,230);
}

KCSubMenu::KCSubMenu(QWidget *parent) :
    QMenu(parent)
{
    showAnimation=new QPropertyAnimation(this, "geometry", this);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);

    indicator=new KCMenuIndicator();
}

KCSubMenu::~KCSubMenu()
{
    indicator->deleteLater();
}

void KCSubMenu::hideEvent(QHideEvent *e)
{
    indicator->hide();
    QMenu::hideEvent(e);
}

void KCSubMenu::showEvent(QShowEvent *e)
{
    QRect parentGeometry=parentWidget()->geometry();
    QRect endPosition=geometry();
    int endWidth=endPosition.width();
    endPosition.setX(parentGeometry.x()+parentGeometry.width()+16);
    endPosition.setWidth(endWidth);
    QRect startPostion=endPosition;
    startPostion.setHeight(0);
    int newIndicatorPosition=startPostion.top()+21;
    startPostion.setTop(newIndicatorPosition);
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
    indicator->setGeometry(startPostion.left()-26,
                           newIndicatorPosition-115,
                           28,
                           230);
    indicator->show();
    showAnimation->start();
    QMenu::showEvent(e);
}

void KCSubMenu::paintEvent(QPaintEvent *e)
{
    QMenu::paintEvent(e);
}
