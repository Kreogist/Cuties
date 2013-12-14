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

#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

#include "kccodecompileprogress.h"

static const int compileProgressHeight=60;

KCCodeCompileProgress::KCCodeCompileProgress(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeCompileProgress");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(compileProgressHeight);

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
    compileProgressDisplay->setMinimum(0);
    compileProgressDisplay->setMaximum(100);
    compileProgressLayout->addWidget(compileProgressDisplay);
}

void KCCodeCompileProgress::setText(const QString &text)
{
    compileProgressText->setText(text);
}

void KCCodeCompileProgress::setValue(const int &value)
{
    compileProgressDisplay->setValue(value);
}

void KCCodeCompileProgress::animeShow()
{
    QPropertyAnimation *showAnimation=new QPropertyAnimation(this, "geometry");
    int geometryArg=parentWidget()->width()/3;
    QRect startGeometry=QRect(geometryArg,
                              -compileProgressHeight,
                              geometryArg,
                              compileProgressHeight);
    QRect endGeometry=startGeometry;
    endGeometry.setTop(0);
    showAnimation->setStartValue(startGeometry);
    showAnimation->setEndValue(endGeometry);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    show();
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void KCCodeCompileProgress::animeHide()
{
    ;
}
