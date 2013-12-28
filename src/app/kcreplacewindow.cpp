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

#include <QTimeLine>

#include "kccolorconfigure.h"

#include "kcreplacewindow.h"

static int replaceWidgetsHeight=25;

KCReplaceWindow::KCReplaceWindow(QWidget *parent) :
    KCSearchWidget(parent)
{
    setObjectName("KCReplaceWindow");
    setContentsMargins(3,2,3,1);
    setMinimumHeight(0);
    setAutoFillBackground(true);

    QPalette pal=palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    mapper=new QSignalMapper(this);

    mainLayout=(QGridLayout *)layout();
    mainLayout->setVerticalSpacing(2);

    replaceText=new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace with"));
    replaceText->setFrame(false);
    replaceText->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceText,1,0,1,KCSearchWidget::searchTextPartWidth);

    replaceButtons[replace]=new QToolButton(this);
    replaceButtons[replace]->setText(tr("Replace"));
    replaceButtons[replace]->setAutoRaise(true);
    replaceButtons[replace]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[replace],1,KCSearchWidget::searchTextPartWidth,1,2);

    replaceButtons[findAndReplace]=new QToolButton(this);
    replaceButtons[findAndReplace]->setText(tr("Find And Replace"));
    replaceButtons[findAndReplace]->setAutoRaise(true);
    replaceButtons[findAndReplace]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[findAndReplace],1,KCSearchWidget::searchTextPartWidth+2,1,2);

    replaceButtons[replaceAll]=new QToolButton(this);
    replaceButtons[replaceAll]->setText(tr("Replace All"));
    replaceButtons[replaceAll]->setAutoRaise(true);
    replaceButtons[replaceAll]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[replaceAll],1,KCSearchWidget::searchTextPartWidth+4,1,2);

    for(int i=0; i<typeCount; i++)
    {
        mapper->setMapping(replaceButtons[i],i);
        connect(replaceButtons[i],SIGNAL(clicked()),mapper,SLOT(map()));
    }
    connect(mapper,SIGNAL(mapped(int)),
            this,SLOT(onOneOfReplaceButtonsClicked(int)));

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    mainLayout->addWidget(closeButton,0,mainLayout->columnCount());

    //Set Button Palette
    pal=closeButton->palette();
    closeButton->setObjectName("KCReplaceWindowCloseButton");
    KCColorConfigure::getInstance()->getPalette(pal,closeButton->objectName());
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, &QToolButton::clicked,
            this, &KCReplaceWindow::hideAnime);

    //Set Original Height.
    setFixedHeight(0);
}

void KCReplaceWindow::showAnime()
{
    QTimeLine *showAnimation=new QTimeLine(250, this);
    showAnimation->setUpdateInterval(1);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showAnimation->setStartFrame(0);
    showAnimation->setEndFrame(61);
    connect(showAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    this->show();
    showAnimation->start();
}

void KCReplaceWindow::resizeDock(int newHeight)
{
    setFixedHeight(newHeight);
}

void KCReplaceWindow::hideAnime()
{
    QTimeLine *hideAnimation=new QTimeLine(250, this);
    hideAnimation->setUpdateInterval(1);
    hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    hideAnimation->setStartFrame(61);
    hideAnimation->setEndFrame(0);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(hideAnimation, &QTimeLine::finished,
            this, &KCReplaceWindow::hide);
    emit requireLostFocus();
    hideAnimation->start();
}

void KCReplaceWindow::onOneOfReplaceButtonsClicked(int type)
{
    QString newText=replaceText->text(),
            oldText=text();
    switch(type)
    {
    case replace:
        emit requireReplace(oldText,newText);
        break;
    case findAndReplace:
        emit requireReplaceAndFind(oldText,newText);
        break;
    case replaceAll:
        emit requireReplaceAll(oldText,newText);
        break;
    default:
        qDebug()<<"unknow replace button type!";
    }
}
