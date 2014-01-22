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

#include "kcpreferencesuperlist.h"

KCPreferenceSuperListContent::KCPreferenceSuperListContent(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);

    //Set super layout
    superListLayout=new QVBoxLayout(this);
    superListLayout->setContentsMargins(0,0,0,0);
    superListLayout->setSpacing(0);
    setLayout(superListLayout);

    //Set current index
    currentItemIndex=-1;

    //Set original height
    originalHeight=0;

    //Set item signal mapper
    superListItemSignalProcessor=new QSignalMapper(this);
    connect(superListItemSignalProcessor, SIGNAL(mapped(int)),
            this, SLOT(transferCurrentIndex(int)));
}

void KCPreferenceSuperListContent::transferCurrentIndex(int newIndex)
{
    if(currentItemIndex==newIndex)
    {
        return;
    }
    if(currentItemIndex!=-1)
    {
        superListItems.at(currentItemIndex)->editFinished();
    }
    currentItemIndex=newIndex;
    setFixedHeight(originalHeight+superListItems.at(currentItemIndex)->getExpandFinishedHeight());
}

void KCPreferenceSuperListContent::resetCurrentIndex()
{
    //If there's a select item, finish edit.
    if(currentItemIndex!=-1)
    {
        superListItems.at(currentItemIndex)->editFinished();
        setFixedHeight(superListLayout->sizeHint().height());
        currentItemIndex=-1;
    }
}

void KCPreferenceSuperListContent::appendTitle(QLabel *newTitleWidget)
{
    superListTitles.append(newTitleWidget);
    superListLayout->addSpacing(5);
    superListLayout->addWidget(newTitleWidget);
    originalHeight=superListLayout->sizeHint().height();
    setFixedHeight(originalHeight);
}

void KCPreferenceSuperListContent::appendItem(KCPreferenceItemBase *newItemWidget)
{
    connect(newItemWidget, SIGNAL(editFocusCapture()),
            superListItemSignalProcessor, SLOT(map()));
    superListItemSignalProcessor->setMapping(newItemWidget, superListItems.count());
    superListItems.append(newItemWidget);
    superListLayout->addWidget(newItemWidget);
    originalHeight=superListLayout->sizeHint().height();
    setFixedHeight(originalHeight);
}

void KCPreferenceSuperListContent::appendStretch()
{
    superListLayout->addStretch();
}

int KCPreferenceSuperListContent::getItemCount()
{
    return superListItems.count();
}

QString KCPreferenceSuperListContent::getItemKey(int itemIndex)
{
    return superListItems.at(itemIndex)->getKeyNames();
}

QVariant KCPreferenceSuperListContent::getItemValue(int itemIndex)
{
    return superListItems.at(itemIndex)->getCurrentValue();
}

KCPreferenceSuperList::KCPreferenceSuperList(QWidget *parent) :
    QScrollArea(parent)
{
    //Set properties.
    setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);

    //Set contents widget
    contents=new KCPreferenceSuperListContent(this);
    setWidget(contents);

    //Set font
    titleFont=this->font();
    titleFont.setPixelSize(20);
}

QLabel *KCPreferenceSuperList::addTitle(const QString &titleText)
{
    QLabel *newTitleWidget=new QLabel(contents);
    newTitleWidget->setText(" " + titleText);
    newTitleWidget->setFont(titleFont);
    newTitleWidget->setFixedHeight(30);
    contents->appendTitle(newTitleWidget);
    return newTitleWidget;
}

KCPreferenceItemCombo *KCPreferenceSuperList::addItemCombo(const QString &captionText,
                                                           const QList<QString> &comboItemList,
                                                           const QString &key)
{
    KCPreferenceItemCombo *newComboItem=new KCPreferenceItemCombo(contents);
    newComboItem->setComboCaptionText(captionText);
    newComboItem->setComboTextList(comboItemList);
    newComboItem->refreshComboText();
    newComboItem->setKeyNames(key);
    newComboItem->setOriginalValue(instance->getValue(key).toInt());
    contents->appendItem(newComboItem);
    return newComboItem;
}

KCPreferenceItemCombo *KCPreferenceSuperList::addItemCombo(KCPreferenceItemCombo *newComboItem)
{
    contents->appendItem(newComboItem);
    return newComboItem;
}

KCPreferenceItemBoolean *KCPreferenceSuperList::addItemBoolean(const QString &captionText,
                                                               const QString &key)
{
    KCPreferenceItemBoolean *newBooleanItem=new KCPreferenceItemBoolean(contents);
    newBooleanItem->setBooleanCaptionText(captionText);
    newBooleanItem->setKeyNames(key);
    newBooleanItem->setOriginalValue(instance->getValue(key).toBool());
    contents->appendItem(newBooleanItem);
    return newBooleanItem;
}

KCPreferenceItemBoolean *KCPreferenceSuperList::addItemBoolean(KCPreferenceItemBoolean *newBooleanItem)
{
    contents->appendItem(newBooleanItem);
    return newBooleanItem;
}

KCPreferenceItemInt *KCPreferenceSuperList::addItemInt(const QString &captionText,
                                                       const QString &key,
                                                       int maxValue,
                                                       int minValue)
{
    KCPreferenceItemInt *newIntItem=new KCPreferenceItemInt(contents);
    newIntItem->setIntCaptionText(captionText);
    newIntItem->setMaximumInt(maxValue);
    newIntItem->setMinimumInt(minValue);
    newIntItem->setKeyNames(key);
    newIntItem->setOriginalValue(instance->getValue(key).toInt());
    contents->appendItem(newIntItem);
    return newIntItem;
}

KCPreferenceItemInt *KCPreferenceSuperList::addItemInt(KCPreferenceItemInt *newIntItem)
{
    contents->appendItem(newIntItem);
    return newIntItem;
}

KCPreferenceItemBooleanGroup *KCPreferenceSuperList::addItemBooleanGroup(const QString &captionText,
                                                                         const QString &key)
{
    KCPreferenceItemBooleanGroup *newBooleanGroupItem=new KCPreferenceItemBooleanGroup(contents);
    newBooleanGroupItem->setBooleanCaptionText(captionText);
    newBooleanGroupItem->setKeyNames(key);
    newBooleanGroupItem->setOriginalValue(instance->getValue(key).toBool());
    contents->appendItem(newBooleanGroupItem);
    return newBooleanGroupItem;
}

KCPreferenceItemPath *KCPreferenceSuperList::addItemPath(KCPreferenceItemPath *newPathItem)
{
    contents->appendItem(newPathItem);
    return newPathItem;
}

KCPreferenceItemPath *KCPreferenceSuperList::addItemPath(const QString &captionText,
                                                         const QString &key,
                                                         QString defaultTitleValue)
{
    KCPreferenceItemPath *newPathItem=new KCPreferenceItemPath(this);
    newPathItem->setPathCaptionText(captionText);
    newPathItem->setKeyNames(key);
    newPathItem->setOriginalValue(instance->getValue(key).toString());
    newPathItem->setDialogTitle(defaultTitleValue);
    contents->appendItem(newPathItem);
    return newPathItem;
}

void KCPreferenceSuperList::addStretch()
{
    contents->appendStretch();
}

void KCPreferenceSuperList::applyPreference()
{
    int itemCount=contents->getItemCount();
    for(int i=0;i<itemCount;i++)
    {
        instance->setValue(contents->getItemKey(i), contents->getItemValue(i));
    }
}

void KCPreferenceSuperList::resetCurrentIndex()
{
    contents->resetCurrentIndex();
}

void KCPreferenceSuperList::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    contents->setFixedWidth(event->size().width());
}
