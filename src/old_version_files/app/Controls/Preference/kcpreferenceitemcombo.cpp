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

#include <QComboBox>
#include <QLabel>

#include "kcpreferenceitemcombo.h"

KCPreferenceItemCombo::KCPreferenceItemCombo(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    //Set Edit Mode Layout
    editLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);
    setLayout(editLayout);

    comboLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    comboLayout->setContentsMargins(0,0,0,0);
    comboLayout->setSpacing(0);

    comboCaption=new QLabel(this);
    comboLayout->addWidget(comboCaption);
    comboLayout->addSpacing(2);
    comboLayout->addWidget(valueDisplayer);
    comboLayout->addWidget(originalValueDisplayer);
    comboLayout->addStretch();

    editLayout->addLayout(comboLayout);

    comboData=new QComboBox(this);
    setEditWidgetStatus(false);
    editLayout->addWidget(comboData);
    editLayout->addStretch();

    setExpandFinishedHeight(50);
}

KCPreferenceItemCombo::~KCPreferenceItemCombo()
{
    comboLayout->deleteLater();
}

void KCPreferenceItemCombo::refreshComboText()
{
    int backupItemChoose=getUserNewValue().toInt();
    comboData->clear();
    for(int i=0; i<comboTextList.count(); i++)
    {
        comboData->addItem(comboTextList.at(i));
    }
    comboData->setCurrentIndex(backupItemChoose);
}

QList<QString> KCPreferenceItemCombo::getComboTextList() const
{
    return comboTextList;
}

void KCPreferenceItemCombo::setComboTextList(const QList<QString> &value)
{
    comboTextList = value;
}

void KCPreferenceItemCombo::setComboCaptionText(const QString &value)
{
    comboCaption->setText(value);
}

void KCPreferenceItemCombo::setEditWidgetStatus(bool states)
{
    comboData->setVisible(states);
    comboData->setEnabled(states);
}

void KCPreferenceItemCombo::setWidgetValue(QVariant newWidgeValue)
{
    comboData->setCurrentIndex(newWidgeValue.toInt());
}

QVariant KCPreferenceItemCombo::getUserNewValue()
{
    return comboData->currentIndex();
}

void KCPreferenceItemCombo::refreshValueDisplay()
{
    valueDisplayer->setText(comboData->currentText());
    if(comboData->currentIndex() == originalValue.toInt())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(QString(" (" +
                                            originalValueIs +
                                            comboTextList.at(originalValue.toInt()) +
                                            ")"));
    setOriginalDisplayVisible(true);
}

void KCPreferenceItemCombo::setOriginalValue(const QVariant &value)
{
    comboData->setCurrentIndex(value.toInt());
    valueDisplayer->setText(comboTextList.at(value.toInt()));
    KCPreferenceItemBase::setOriginalValue(value);

    connect(comboData, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChangedEvent()));
}
