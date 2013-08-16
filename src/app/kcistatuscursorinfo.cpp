/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
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

#include "kcistatuscursorinfo.h"

kciStatusCursorInfo::kciStatusCursorInfo(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);

    QHBoxLayout *TextLayout=new QHBoxLayout(this);
    TextLayout->setContentsMargins(0,0,0,0);
    TextLayout->setSpacing(0);
    setLayout(TextLayout);

    lblCursorPosition=new QLabel(this);
    TextLayout->addWidget(lblCursorPosition);

    spbLineNum=new QSpinBox(this);
    spbLineNum->setContentsMargins(0,0,0,0);
    spbLineNum->setMinimum(1);
    spbLineNum->hide();
    connect(spbLineNum,SIGNAL(valueChanged(int)),
            this,SLOT(gotoLineNumber(int)));
    connect(spbLineNum,SIGNAL(editingFinished()),
            this,SLOT(finishedHideGotoBox()));
    gotoBarShowed=false;

    setFixedHeight(spbLineNum->height());

    gotoHideAnime=new QPropertyAnimation(spbLineNum,"geometry",this);
    connect(gotoHideAnime,SIGNAL(finished()),
            this,SLOT(setHideGotoBox()));
}

void kciStatusCursorInfo::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    spbLineNum->setFixedWidth(this->width());
}

void kciStatusCursorInfo::ShowGotoBox(int currentValue, int MaxValue)
{
    spbLineNum->setValue(currentValue);
    spbLineNum->setMaximum(MaxValue);
    spbLineNum->selectAll();
    spbLineNum->show();

    if(!gotoBarShowed)
    {
        QPropertyAnimation *gotoAnime=new QPropertyAnimation(spbLineNum,"geometry");
        QRect animeEndPos=QRect(0,0,this->width(),this->height());
        QRect animeStartPos=animeEndPos;
        animeStartPos.setTop(animeStartPos.height()+3);
        gotoAnime->setStartValue(animeStartPos);
        gotoAnime->setEndValue(animeEndPos);
        gotoAnime->setEasingCurve(QEasingCurve::OutCubic);
        spbLineNum->show();
        gotoAnime->start();
        gotoBarShowed=true;
    }
    spbLineNum->setFocus();
}

bool kciStatusCursorInfo::getGotoShowed()
{
    return gotoBarShowed;
}

void kciStatusCursorInfo::updateCursorPosition(int LineNum, int ColNum)
{
    if(LineNum>0)
    {
        lblCursorPosition->setText(QString(tr("Line ")) +
                                   QString::number(LineNum) +
                                   QString(tr(", ")) +
                                   QString(tr("Col ")) +
                                   QString::number(ColNum) +
                                   QString(tr(" ")));
    }
    else
    {
        lblCursorPosition->setText("");
        HideGotoBox();
    }
    this->resize(lblCursorPosition->size());
}

void kciStatusCursorInfo::finishedHideGotoBox()
{
    HideGotoBox();
}

void kciStatusCursorInfo::gotoLineNumber(int NewNum)
{
    emit ToLineNum(NewNum);
}

void kciStatusCursorInfo::HideGotoBox()
{
    if(gotoBarShowed)
    {
        gotoBarShowed=false;
        QRect animeStartPos=spbLineNum->rect();
        QRect animeEndPos=animeStartPos;
        animeEndPos.setY(spbLineNum->height());
        gotoHideAnime->setStartValue(animeStartPos);
        gotoHideAnime->setEndValue(animeEndPos);
        gotoHideAnime->setEasingCurve(QEasingCurve::OutCubic);
        gotoHideAnime->start();
    }
}

void kciStatusCursorInfo::setHideGotoBox()
{
    spbLineNum->hide();
}
