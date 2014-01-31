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


#include <QDebug>

#include "kcpreferencepager.h"

KCPreferencePager::KCPreferencePager(QWidget *parent) :
    QWidget(parent)
{
    //Set basic content
    setAutoFillBackground(true);

    //Set palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    //Set current page index
    currentPageIndex=-1;

    //Set animation group
    moveAnimationGroup=new QParallelAnimationGroup(this);
}

void KCPreferencePager::addSuperList(KCPreferenceSuperList *newSuperList)
{
    newSuperList->setEnabled(false);
    newSuperList->setVisible(false);
    preferenceSuperLists.append(newSuperList);
}

void KCPreferencePager::initPager()
{
    currentPageIndex=0;
    setPageVisible(currentPageIndex, true);
}

void KCPreferencePager::setPageVisible(int pageIndex, bool visible)
{
    preferenceSuperLists.at(pageIndex)->setVisible(visible);
    preferenceSuperLists.at(pageIndex)->setEnabled(visible);
}

void KCPreferencePager::switchToPage(int pageIndex)
{
    moveAnimationGroup->stop();
    moveAnimationGroup->clear();

    preferenceSuperLists.at(currentPageIndex)->resetCurrentIndex();
    QPropertyAnimation *throwLastPage=new QPropertyAnimation(preferenceSuperLists.at(currentPageIndex), "geometry", this);
    QPropertyAnimation *putCurrentPage=new QPropertyAnimation(preferenceSuperLists.at(pageIndex), "geometry", this);
    throwLastPage->setEasingCurve(QEasingCurve::OutCubic);
    putCurrentPage->setEasingCurve(QEasingCurve::OutCubic);
    throwLastPage->setDuration(200);
    putCurrentPage->setDuration(200);
    QRect currentPosition=preferenceSuperLists.at(currentPageIndex)->rect();
    QRect lastEndPosition=currentPosition;
    QRect throwFromPosition=currentPosition;
    backupPage=currentPageIndex;
    if(pageIndex > currentPageIndex)
    {
        //This page is under the current page, move up
        throwFromPosition.setTop(lastEndPosition.height());
        lastEndPosition.setTop(-lastEndPosition.height());
    }
    else
    {
        //This page is above the current page, move down
        throwFromPosition.setTop(-lastEndPosition.height());
        lastEndPosition.setTop(lastEndPosition.height()+10);
    }
    throwLastPage->setStartValue(currentPosition);
    throwLastPage->setEndValue(lastEndPosition);
    putCurrentPage->setStartValue(throwFromPosition);
    putCurrentPage->setEndValue(currentPosition);
    preferenceSuperLists.at(pageIndex)->setGeometry(throwFromPosition);
    moveAnimationGroup->addAnimation(throwLastPage);
    moveAnimationGroup->addAnimation(putCurrentPage);
    connect(moveAnimationGroup, SIGNAL(finished()),
            this, SLOT(hideBackupPage()));
    setPageVisible(pageIndex, true);
    moveAnimationGroup->start();
    currentPageIndex=pageIndex;
}

void KCPreferencePager::hideBackupPage()
{
    setPageVisible(backupPage, false);
}

void KCPreferencePager::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    for(int i=0; i<preferenceSuperLists.count(); i++)
    {
        preferenceSuperLists.at(i)->resize(event->size());
    }
}
