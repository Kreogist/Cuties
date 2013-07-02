/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  kcititlebar.cpp is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcititlebar.h"

kciTitleBar::kciTitleBar(QWidget *parent) :
    QWidget(parent),
    mainWindow(parent)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);

    windowTitle=parent->windowTitle();

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
    connect(mainButton,SIGNAL(clicked()),mainButton,SLOT(showMenu()));
    mainButton->setPalette(bpal);

    titleLabel=new QLabel(windowTitle,this);
    QPalette pal=titleLabel->palette();
    pal.setColor(QPalette::WindowText,QColor(208,208,208));
    titleLabel->setPalette(pal);

    hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    setLayout(hLayout);
    hLayout->addWidget(mainButton);
    hLayout->addStretch();
    hLayout->addWidget(titleLabel);
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
}

void kciTitleBar::_exchange_button_state()
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

void kciTitleBar::setWindowMin()
{
    mainWindow->showMinimized();
}

void kciTitleBar::setWindowNormal()
{
    mainWindow->showNormal();
    maximizeButton->setIcon(maximizeButtonIcon);
    isShowingNormalButton=false;
}

void kciTitleBar::setWindowMax()
{
    mainWindow->showMaximized();
    maximizeButton->setIcon(normalButtonIcon);
    isShowingNormalButton=true;
}

void kciTitleBar::setMenu(QMenu *menu)
{
    mainButton->setMenu(menu);
}

void kciTitleBar::setMainButtonIcon(const QString &mainIcon)
{
    mainButtonIcon.addFile(mainIcon);
    mainButton->setIcon(mainButtonIcon);
}

void kciTitleBar::mousePressEvent(QMouseEvent *event)
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
        event->ignore();
}

void kciTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(!isShowingNormalButton)
    {
        if(hasPressed && event->buttons() == Qt::LeftButton)
        {
            mainWindow->move(mainWindow->pos() + event->pos() - mousePosStart);
        }
    }
}

void kciTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(hasPressed)
    {
        hasPressed=false;
        event->accept();
    }
    else
        event->ignore();
}

void kciTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _exchange_button_state();
    }
}

void kciTitleBar::setTitle(const QString &title)
{
    titleLabel->setText(title);
}
