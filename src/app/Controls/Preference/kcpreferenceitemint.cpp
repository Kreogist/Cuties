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

#include "kcpreferenceitemint.h"

KCPreferenceItemInt::KCPreferenceItemInt(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    //Set Edit Mode Layout
    dialLayout=new QHBoxLayout(this);
    dialLayout->setContentsMargins(0,0,0,0);
    dialLayout->setSpacing(0);
    setLayout(dialLayout);

    editLayout=new QVBoxLayout();
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);

    intLayout=new QHBoxLayout();
    intLayout->setContentsMargins(0,0,0,0);
    intLayout->setSpacing(0);

    intCaption=new QLabel(this);
    intLayout->addWidget(intCaption);
    intLayout->addSpacing(2);
    intLayout->addWidget(valueDisplayer);
    intLayout->addWidget(originalValueDisplayer);
    intLayout->addStretch();

    editLayout->addLayout(intLayout);

    intSliderLayout=new QHBoxLayout();
    intSliderLayout->setContentsMargins(0,0,0,0);
    intSliderLayout->setSpacing(0);
    intSpinValueChanger=new QSpinBox(this);
    intSpinValueChanger->setContentsMargins(0,0,0,0);
    intSliderValueChanger=new QSlider(Qt::Horizontal, this);
    intSliderValueChanger->setContentsMargins(0,0,0,0);
    intDialValueChanger=new QDial(this);
    intDialValueChanger->setContentsMargins(0,0,0,0);
    intDialValueChanger->setFixedSize(52,52);
    setEditWidgetStatus(false);
    connect(intSpinValueChanger, SIGNAL(valueChanged(int)),
            this, SLOT(syncValue(int)));
    connect(intSliderValueChanger, SIGNAL(valueChanged(int)),
            this, SLOT(syncValue(int)));
    connect(intDialValueChanger, SIGNAL(valueChanged(int)),
            this, SLOT(syncValue(int)));

    intSliderLayout->addWidget(intSpinValueChanger);
    intSliderLayout->addWidget(intSliderValueChanger);
    editLayout->addLayout(intSliderLayout);
    editLayout->addStretch();
    dialLayout->addLayout(editLayout);
    dialLayout->addWidget(intDialValueChanger);

    setExpandFinishedHeight(52);
}

KCPreferenceItemInt::~KCPreferenceItemInt()
{
    editLayout->deleteLater();
    intLayout->deleteLater();
    intSliderLayout->deleteLater();
}

void KCPreferenceItemInt::setOriginalValue(const QVariant &value)
{
    syncValue(value.toInt());
    valueDisplayer->setText(QString::number(value.toInt()));
    KCPreferenceItemBase::setOriginalValue(value);

    connect(intSpinValueChanger, SIGNAL(valueChanged(int)),
            this, SLOT(valueChangedEvent()));
}

void KCPreferenceItemInt::setIntCaptionText(const QString &value)
{
    intCaption->setText(value);
}

void KCPreferenceItemInt::setMaximumInt(const int &itemMax)
{
    intSpinValueChanger->setMaximum(itemMax);
    intSliderValueChanger->setMaximum(itemMax);
    intDialValueChanger->setMaximum(itemMax);
}

void KCPreferenceItemInt::setMinimumInt(const int &itemMin)
{
    intSpinValueChanger->setMinimum(itemMin);
    intSliderValueChanger->setMinimum(itemMin);
    intDialValueChanger->setMinimum(itemMin);
}

void KCPreferenceItemInt::syncValue(int newValue)
{
    intSpinValueChanger->setValue(newValue);
    intSliderValueChanger->setValue(newValue);
    intDialValueChanger->setValue(newValue);
}

void KCPreferenceItemInt::setEditWidgetStatus(bool states)
{
    intSpinValueChanger->setEnabled(states);
    intSpinValueChanger->setVisible(states);
    intSliderValueChanger->setEnabled(states);
    intSliderValueChanger->setVisible(states);
    intDialValueChanger->setEnabled(states);
    intDialValueChanger->setVisible(states);
}

void KCPreferenceItemInt::setWidgetValue(QVariant newWidgeValue)
{
    syncValue(newWidgeValue.toInt());
}

QVariant KCPreferenceItemInt::getUserNewValue()
{
    return intSpinValueChanger->value();
}

void KCPreferenceItemInt::refreshValueDisplay()
{
    valueDisplayer->setText(intSpinValueChanger->text());
    if(intSpinValueChanger->value() == originalValue.toInt())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(" (" +
                                    originalValueIs +
                                    QString::number(originalValue.toInt()) +
                                    ")");
    setOriginalDisplayVisible(true);
}


