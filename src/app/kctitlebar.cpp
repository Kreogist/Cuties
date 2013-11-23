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

#include "kctitlebar.h"

KCTitleBar::KCTitleBar(QWidget *parent) :
    QWidget(parent),
    mainWindow(parent)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(32);

    windowTitle=parent->windowTitle();

    hasPressed=false;

    QPalette pal;

#ifndef Q_OS_MACX
    mainButton=new QToolButton(this);
    mainButton->setAutoRaise(true);
    mainButton->setFixedSize(32,32);
    pal=mainButton->palette();
    pal.setColor(QPalette::Window, QColor(0x9c, 0x9c, 0x9c));
    pal.setColor(QPalette::Button, QColor(0xf7,0xcf,0x3d));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    mainButton->setPalette(pal);
    mainButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_1));
    connect(mainButton, &QToolButton::pressed,
            mainButton, &QToolButton::showMenu);
#endif

    mainToolBar=new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");
    pal=mainToolBar->palette();
    KCColorConfigure::getInstance()->getPalette(pal,mainToolBar->objectName());
    mainToolBar->setPalette(pal);
    mainToolBar->setContentsMargins(0,0,0,0);
    mainToolBar->setMovable(true);
#ifdef Q_OS_MACX
    mainToolBar->setGeometry(0,
#else
    mainToolBar->setGeometry(mainButton->width(),
#endif
                             0,
                             mainToolBar->width(),
                             mainToolBar->height());
    mainToolBar->hide();
    toolbarShown=false;

    tlbShowAnime=new QPropertyAnimation(mainToolBar,"geometry",this);
    tlbHideAnime=new QPropertyAnimation(mainToolBar,"geometry",this);
    connect(tlbHideAnime,SIGNAL(finished()),mainToolBar,SLOT(hide()));

#ifdef Q_OS_MACX
    this->hide();
    connect(tlbHideAnime,SIGNAL(finished()),this,SLOT(hide()));
#endif
}

void KCTitleBar::showToolBar()
{
    if(!toolbarShown)
    {
        tlbHideAnime->stop();
        QRect animeEndPos=mainToolBar->geometry();
#ifdef Q_OS_MACX
        animeEndPos.setLeft(0);
        this->show();
#else
        animeEndPos.setLeft(mainButton->width());
#endif
        animeEndPos.setTop(0);
        QRect animeStartPos=animeEndPos;
        animeStartPos.setTop(-mainToolBar->height());
        tlbShowAnime->setStartValue(animeStartPos);
        tlbShowAnime->setEndValue(animeEndPos);
        tlbShowAnime->setEasingCurve(QEasingCurve::OutCubic);
        mainToolBar->show();
        toolbarShown=true;

        //Start Animation.
        tlbShowAnime->start();
    }
}

void KCTitleBar::hideToolBar()
{
    if(toolbarShown)
    {
        tlbShowAnime->stop();
        QRect animeStartPos=mainToolBar->geometry();
        QRect animeEndPos=animeStartPos;
        animeEndPos.setTop(-mainToolBar->height()*2);
        tlbHideAnime->setStartValue(animeStartPos);
        tlbHideAnime->setEndValue(animeEndPos);
        tlbHideAnime->setEasingCurve(QEasingCurve::OutCubic);
        tlbHideAnime->start();
        toolbarShown=false;
    }
}

void KCTitleBar::addToolSeparator()
{
    mainToolBar->addSeparator();
    mainToolBar->setFixedWidth(mainToolBar->width()+3);
}

void KCTitleBar::addToolButton(QToolButton *tblMainButton)
{
    mainToolBar->addWidget(tblMainButton);
    mainToolBar->setFixedWidth(mainToolBar->sizeHint().width());
}

#ifndef Q_OS_MACX
void KCTitleBar::setMenu(QMenu *menu)
{
    mainButton->setMenu(menu);
}

void KCTitleBar::setMainButtonIcon(const QString &mainIcon)
{
    QPixmap mainButtonImage(mainIcon);
    mainButton->setIcon(QIcon(mainIcon));
    mainButton->setIconSize(QSize(mainButtonImage.width(),mainButtonImage.height()));
}
#endif
