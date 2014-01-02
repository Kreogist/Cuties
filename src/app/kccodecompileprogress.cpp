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

#include <QDebug>
#include <QVBoxLayout>
#include <QTimer>
#include <QGraphicsDropShadowEffect>

#include "kccodecompileprogress.h"
#include "kccompilerconfigure.h"

int KCCodeCompileProgress::compileProgressWidth = 280;
int KCCodeCompileProgress::compileProgressHeight = 60;

KCCodeCompileProgress::KCCodeCompileProgress(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeCompileProgress");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedSize(compileProgressWidth,
                 compileProgressHeight);

    QGraphicsDropShadowEffect *shadowEffect=new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15.0);
    shadowEffect->setColor(QColor(0, 0, 0, 200));
    shadowEffect->setOffset(0);
    setGraphicsEffect(shadowEffect);

    QVBoxLayout *compileProgressLayout=new QVBoxLayout(this);
    compileProgressLayout->setContentsMargins(7,7,7,7);
    compileProgressLayout->setSpacing(7);
    setLayout(compileProgressLayout);

    compileProgressText=new QLabel(this);
    compileProgressText->setAlignment(Qt::AlignHCenter);
    compileProgressLayout->addWidget(compileProgressText);

    compileProgressDisplay=new QProgressBar(this);
    compileProgressDisplay->setTextVisible(false);
    compileProgressDisplay->setMinimum(0);
    compileProgressDisplay->setMaximum(100);
    compileProgressLayout->addWidget(compileProgressDisplay);
    progressPal=compileProgressDisplay->palette();
    progressColor=progressPal.color(QPalette::Highlight);
    originalColor=progressColor;

    animation=new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    timeoutCounter=new QTimer(this);
    connect(timeoutCounter, SIGNAL(timeout()), this, SLOT(refreshTimemout()));
}

void KCCodeCompileProgress::countToCompile()
{
    if(KCCompilerConfigure::getInstance()->getDelayCompile())
    {
        setProgressColor(originalColor);
        setCompileState(certifyCompile);
        compileProgressDisplay->setValue(100);
        timeoutCounter->start(KCCompilerConfigure::getInstance()->getDelayTimeout());
    }
    else
    {
        compileProgressDisplay->setValue(0);
        emit requireCompile();
    }
}

void KCCodeCompileProgress::regeometry(int w)
{
    int nX=(w-compileProgressWidth)/2;
    bool animationRunning=(animation->state()==QAbstractAnimation::Running);
    animation->stop();
    move(nX, y());
    if(animationRunning)
    {
        QRect startGeometry=animation->startValue().toRect();
        QRect endGeometry=animation->endValue().toRect();
        startGeometry.setX(nX);
        startGeometry.setWidth(compileProgressWidth);
        endGeometry.setX(nX);
        endGeometry.setWidth(compileProgressWidth);
        animation->setStartValue(startGeometry);
        animation->setEndValue(endGeometry);
        animation->start();
    }
}

void KCCodeCompileProgress::setText(const QString &text)
{
    compileProgressText->setText(text);
}

void KCCodeCompileProgress::setValue(const int &value)
{
    compileProgressDisplay->setValue(value);
}

void KCCodeCompileProgress::showCompileSuccess()
{
    setCompileState(compileSuccess);
}

void KCCodeCompileProgress::showCompileError(int errors)
{
    setCompileState(errorCompileError);
    setText(QString(QString::number(errors) + " " +
                     tr("errors occured.")));
    setValue(100);
    setProgressColor(QColor(255,0,0));
    delayHide();
}

void KCCodeCompileProgress::delayHide()
{
    if(currentState < compileSuccess)
    {
        return;
    }
    else if(currentState==compileSuccess)
    {
        QTimer::singleShot(1000, this, SLOT(animeHide()));
    }
    else
    {
        QTimer::singleShot(2000, this, SLOT(animeHide()));
    }
}

void KCCodeCompileProgress::animeShow()
{
    //Stop all animation for no reason.
    animation->stop();
    disconnect(hideConnection);
    QRect startGeometry=geometry();
    QRect endGeometry=startGeometry;
    endGeometry.setTop(0);
    endGeometry.setHeight(compileProgressHeight);
    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);
    show();
    animation->start();
}

void KCCodeCompileProgress::animeHide()
{
    //Stop all animation for no reason.
    animation->stop();

    disconnect(hideConnection);
    //reconnect it.
    hideConnection=connect(animation, SIGNAL(finished()),
                           this, SLOT(hide()));
    QRect startGeometry=geometry();
    QRect endGeometry=startGeometry;
    endGeometry.setTop(-compileProgressHeight-5);
    endGeometry.setHeight(compileProgressHeight);
    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);
    animation->start();
}

void KCCodeCompileProgress::refreshTimemout()
{
    compileProgressDisplay->setValue(compileProgressDisplay->value()-5);
    if(compileProgressDisplay->value()==0)
    {
        timeoutCounter->stop();
        emit requireCompile();
    }
}

void KCCodeCompileProgress::setProgressColor(QColor color)
{
    progressColor=color;
    progressPal.setColor(QPalette::Highlight, progressColor);
    compileProgressDisplay->setPalette(progressPal);
}

void KCCodeCompileProgress::setCompileState(KCCodeCompileProgress::CompileState stateValue)
{
    currentState=stateValue;
    switch(stateValue)
    {
    case certifyCompile:
        setText(tr("Certify Compile"));
        break;
    case checkingCompiler:
        setText(tr("Checking Compiler"));
        setValue(33);
        break;
    case runningCompiler:
        setText(tr("Compiling"));
        setValue(67);
        break;
    case compileSuccess:
        setText(tr("Compile Success"));
        setValue(100);
        setProgressColor(QColor(0,255,0));
        delayHide();
        break;
    case errorCantFindCompiler:
        setText(tr("Can't find compiler."));
        setValue(100);
        break;
    default:
        break;
    }
}
