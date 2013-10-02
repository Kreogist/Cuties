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

#ifndef Q_OS_MACX
KCITitleBarAutoFill::KCITitleBarAutoFill(QWidget *parent) :
    QWidget(parent)
{
}

void KCITitleBarAutoFill::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->accept();
    if(e->button() == Qt::LeftButton)
    {
        emit dblClickEmit();
    }
}
#endif

KCITitleBar::KCITitleBar(QWidget *parent) :
    QWidget(parent),
    mainWindow(parent)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(32);

    windowTitle=parent->windowTitle();

    hasPressed=false;

#ifndef Q_OS_MACX
    closeButton = new QToolButton(this);
    closeButton->setIcon(QIcon(QString(":/toolbutton/image/Close.png")));

    QPalette bpal=closeButton->palette();
    bpal.setColor(QPalette::Button, QColor(83,83,83));
    closeButton->setPalette(bpal);

    minimizeButton = new QToolButton(this);
    minimizeButton->setIcon(QIcon(QString(":/toolbutton/image/Minimized.png")));
    minimizeButton->setPalette(bpal);

    maximizeButton = new QToolButton(this);
    maximizeButtonIcon=QIcon(QString(":/toolbutton/image/Maxmized.png"));
    maximizeButton->setIcon(maximizeButtonIcon);
    maximizeButton->setPalette(bpal);
    isShowingNormalButton = false;

    normalButtonIcon=QIcon(QString(":/toolbutton/image/Normalmized.png"));

    connect(closeButton,SIGNAL(clicked()),this->parent(),SLOT(close()));
    connect(minimizeButton,SIGNAL(clicked()),
            this->parent(),SLOT(showMinimized()));
    connect(maximizeButton,SIGNAL(clicked()),
            this,SLOT(_exchange_button_state()));
    mainButton=new QToolButton(this);
    mainButton->setAutoRaise(true);
    mainButton->setFixedHeight(32);
    mainButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_1));
    connect(mainButton,SIGNAL(clicked()),mainButton,SLOT(showMenu()));
    mainButton->setPalette(bpal);
#endif

    mainToolBar=new QToolBar(this);
    QPalette pal=mainToolBar->palette();
    pal.setColor(QPalette::Button, QColor(83,83,83));
    mainToolBar->setPalette(pal);
    mainToolBar->setContentsMargins(0,0,0,0);
    mainToolBar->setMovable(true);
#ifdef Q_OS_MACX
    mainToolBar->setGeometry(0,
                             0,
                             mainToolBar->width(),
                             mainToolBar->height());
#else
    mainToolBar->setGeometry(mainButton->width(),
                             0,
                             mainToolBar->width(),
                             mainToolBar->height());

    autoFill=new KCITitleBarAutoFill(this);
    connect(autoFill, SIGNAL(dblClickEmit()),
            this, SLOT(spacingDblClick()));
#endif
    mainToolBar->hide();
    toolbarShown=false;

    NoUseSpacing=new QSpacerItem(0,this->height());

    hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    setLayout(hLayout);

#ifndef Q_OS_MACX
    hLayout->addWidget(mainButton);
    hLayout->addSpacerItem(NoUseSpacing);
    hLayout->addWidget(autoFill, 1);

    hLayout->addSpacing(3);

    vMinLayout = new QVBoxLayout();
    minimizeButton->setFixedWidth(30);
    minimizeButton->setFixedHeight(20);
    vMinLayout->addWidget(minimizeButton);
    vMinLayout->addStretch();
    hLayout->addLayout(vMinLayout);

    vMaxLayout = new QVBoxLayout();
    maximizeButton->setFixedHeight(20);
    maximizeButton->setFixedWidth(30);
    vMaxLayout->addWidget(maximizeButton);
    vMaxLayout->addStretch();
    hLayout->addLayout(vMaxLayout);

    vCloseLayout = new QVBoxLayout();
    closeButton->setFixedWidth(50);
    closeButton->setFixedHeight(20);
    vCloseLayout->addWidget(closeButton);
    vCloseLayout->addStretch();
    hLayout->addLayout(vCloseLayout);
#endif

    tlbShowAnime=new QPropertyAnimation(mainToolBar,"geometry",this);
    tlbHideAnime=new QPropertyAnimation(mainToolBar,"geometry",this);
    connect(tlbHideAnime,SIGNAL(finished()),mainToolBar,SLOT(hide()));

#ifdef Q_OS_MACX
    this->hide();
    connect(tlbHideAnime,SIGNAL(finished()),this,SLOT(hide()));
#endif
}

void KCITitleBar::showToolBar()
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
        NoUseSpacing->changeSize(mainToolBar->width(),this->height());
        mainToolBar->show();
        toolbarShown=true;

        //Start Animation.
        tlbShowAnime->start();
    }
}

void KCITitleBar::hideToolBar()
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
        NoUseSpacing->changeSize(0,this->height());
        tlbHideAnime->start();
        toolbarShown=false;
    }
}

void KCITitleBar::addToolSeparator()
{
    mainToolBar->addSeparator();
    mainToolBar->setFixedWidth(mainToolBar->width()+3);
}

void KCITitleBar::addToolButton(QToolButton *tblMainButton)
{
    mainToolBar->addWidget(tblMainButton);
    mainToolBar->setFixedWidth(mainToolBar->width()+25);
}

void KCITitleBar::_exchange_button_state()
{
    if(isShowingNormalButton)
    {
        setWindowNormal();
    }
    else
    {
        setWindowMax();
    }
}

void KCITitleBar::setWindowMin()
{
    mainWindow->showMinimized();
}

void KCITitleBar::setWindowNormal()
{
    mainWindow->showNormal();
    maximizeButton->setIcon(maximizeButtonIcon);
    isShowingNormalButton=false;
}

void KCITitleBar::setWindowMax()
{
    mainWindow->showMaximized();
    maximizeButton->setIcon(normalButtonIcon);
    isShowingNormalButton=true;
}

#ifndef Q_OS_MACX
void KCITitleBar::setMenu(QMenu *menu)
{
    mainButton->setMenu(menu);
}

void KCITitleBar::setMainButtonIcon(const QString &mainIcon)
{
    mainButtonIcon.addFile(mainIcon);
    mainButton->setIcon(mainButtonIcon);
}

void KCITitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton &&
       event->pos().x()>=this->pos().x() &&
       event->pos().y()>=this->pos().y() &&
       event->pos().x()<=this->pos().x()+this->width()&&
       event->pos().y()<=this->pos().y()+this->height())
    {
        hasPressed=true;
        mousePosStart=event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void KCITitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(!isShowingNormalButton && hasPressed && event->buttons() == Qt::LeftButton)
    {
        mainWindow->move(mainWindow->pos() + event->pos() - mousePosStart);
    }
}

void KCITitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(hasPressed)
    {
        hasPressed=false;
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void KCITitleBar::spacingDblClick()
{
    _exchange_button_state();
}
#endif
