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

#include "kclanguageconfigure.h"
#include "kcstatuscursorinfo.h"

KCStatusCursorInfo::KCStatusCursorInfo(QWidget *parent) :
    QWidget(parent)
{
    retranslate();
    setContentsMargins(2,0,5,0);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QHBoxLayout *textLayout=new QHBoxLayout(this);
    textLayout->setContentsMargins(0,0,0,0);
    textLayout->setSpacing(0);
    setLayout(textLayout);

    cursorPosition=new QLabel(this);
    cursorPosition->setContentsMargins(0,0,0,0);
    textLayout->addWidget(cursorPosition);

    gotoLineNum=new QSpinBox(this);
    gotoLineNum->setContentsMargins(0,0,0,0);
    gotoLineNum->setMinimumHeight(0);
    gotoLineNum->setMinimum(1);
    gotoLineNum->hide();
    connect(gotoLineNum,SIGNAL(valueChanged(int)),
            this,SLOT(gotoLineNumber(int)));
    connect(gotoLineNum,SIGNAL(editingFinished()),
            this,SLOT(finishedHideGotoBox()));
    gotoBarShowed=false;

    setFixedHeight(gotoLineNum->height());

    gotoHideAnime=new QPropertyAnimation(gotoLineNum,"geometry",this);
    connect(gotoHideAnime,SIGNAL(finished()),
            this,SLOT(setHideGotoBox()));

    lineNumString=QString("");
    columnNumString=QString("");

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCStatusCursorInfo::retranslateAndSet);
}

void KCStatusCursorInfo::retranslate()
{
    lineTextBegin=tr("Line ");
    lineTextEnd=tr(", ");
    colTextBegin=tr("Column ");
    colTextEnd=tr(".");
}

void KCStatusCursorInfo::retranslateAndSet()
{
    retranslate();
    refresh();
}

void KCStatusCursorInfo::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    emit sizeChanged();
}

void KCStatusCursorInfo::showGotoBox(int currentValue, int maxValue)
{
    if(!gotoBarShowed)
    {
        gotoLineNum->setFixedWidth(width());
        gotoBarResize=connect(this, &KCStatusCursorInfo::sizeChanged,
                              this, &KCStatusCursorInfo::resizeGotoBox);
        gotoLineNum->setValue(currentValue);
        gotoLineNum->setMaximum(maxValue);
        gotoLineNum->selectAll();
        gotoLineNum->show();
        QPropertyAnimation *gotoAnime=new QPropertyAnimation(gotoLineNum,"geometry");
        QRect animeEndPos=QRect(0,0,this->width(),this->height());
        QRect animeStartPos=animeEndPos;
        animeStartPos.setTop(animeStartPos.height()+3);
        gotoAnime->setStartValue(animeStartPos);
        gotoAnime->setEndValue(animeEndPos);
        gotoAnime->setEasingCurve(QEasingCurve::OutCubic);
        gotoLineNum->show();
        gotoAnime->start();
        gotoBarShowed=true;
    }
    gotoLineNum->setFocus();
}

bool KCStatusCursorInfo::getGotoShowed()
{
    return gotoBarShowed;
}

void KCStatusCursorInfo::refresh()
{
    if(!lineNumString.isEmpty())
    {
        cursorPosition->setText(QString(lineTextBegin+
                                lineNumString+
                                lineTextEnd+
                                colTextBegin+
                                columnNumString+
                                colTextEnd));
    }
    else
    {
        cursorPosition->setText("");
        hideGotoBox();
    }
    resize(cursorPosition->size());
}

void KCStatusCursorInfo::updateCursorPosition(int newLineNum, int newColumnNum)
{
    newLineNum++;
    if(newLineNum>0)
    {
        lineNumString=QString::number(newLineNum);
        columnNumString=QString::number(newColumnNum+1);
    }
    else
    {
        lineNumString.clear();
        columnNumString.clear();
    }
    refresh();
}

void KCStatusCursorInfo::finishedHideGotoBox()
{
    hideGotoBox();
}

void KCStatusCursorInfo::gotoLineNumber(int newLineNum)
{
    emit toNewLineNum(newLineNum);
}

void KCStatusCursorInfo::hideGotoBox()
{
    if(gotoBarShowed)
    {
        gotoBarShowed=false;
        QRect animeStartPos=gotoLineNum->rect();
        QRect animeEndPos=animeStartPos;
        animeEndPos.setY(gotoLineNum->height());
        gotoHideAnime->setStartValue(animeStartPos);
        gotoHideAnime->setEndValue(animeEndPos);
        gotoHideAnime->setEasingCurve(QEasingCurve::OutCubic);
        gotoHideAnime->start();
        disconnect(gotoBarResize);
    }
}

void KCStatusCursorInfo::setHideGotoBox()
{
    gotoLineNum->hide();
}

void KCStatusCursorInfo::resizeGotoBox()
{
    gotoLineNum->setFixedWidth(width());
}

