/*
 *
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

#include <QClipboard>
#include <QApplication>
#include <QRegularExpression>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>

#include "kcclipboard.h"

KCClipboard *KCClipboard::instance=nullptr;

KCClipboard::KCClipboard()
{
    clipboardTextsModel=new QStandardItemModel(this);
    clipboardTextsModelRoot=clipboardTextsModel->invisibleRootItem();

    systemClipboard=qApp->clipboard();

    connect(systemClipboard,&QClipboard::dataChanged,
            this,&KCClipboard::onSystemClipboardChanged);
}

KCClipboard *KCClipboard::getInstance()
{
    return instance==nullptr?instance=new KCClipboard:instance;
}

void KCClipboard::onSystemClipboardChanged()
{
    if(!ignoreSignal)
    {
        addToClipboardStack(systemClipboard->text());
    }
    else
    {
        ignoreSignal=false;
    }
}

QStandardItemModel *KCClipboard::getClipboardTextsModel() const
{
    return clipboardTextsModel;
}

void KCClipboard::setClipboardTextsModel(QStandardItemModel *value)
{
    clipboardTextsModel = value;
}

QString KCClipboard::getHistoryClipboardText(int itemIndex)
{
    QString newClipData=clipboardTextsModel->item(itemIndex)->toolTip();
    ignoreSignal=true;
    systemClipboard->setText(newClipData);
    return newClipData;
}

int KCClipboard::getMaxDataCount()
{
    return maxDataCount;
}

void KCClipboard::setMaxDataCount(int value)
{
    if(maxDataCount>value)
    {
        do
        {
            clipboardTextsModelRoot->removeRow(clipboardTextsModelRoot->rowCount()-1);
        }
        while(clipboardTextsModelRoot->rowCount() > value);
    }
    maxDataCount = value;
}

void KCClipboard::addToClipboardStack(QString _text)
{
    QString _caption;
    int firstChar=_text.indexOf(QRegularExpression("\\S"));
    if(firstChar!=-1)
    {
        _caption=_text.mid(firstChar);
    }
    firstChar=_caption.indexOf("\n"); //firstChar now becomes firstNextLineChar.
    if(firstChar!=-1)
    {
        _caption=_caption.left(firstChar-1)+"...";
    }

    QStandardItem *clipItem=new QStandardItem(_caption);
    clipItem->setEditable(false);
    clipItem->setToolTip(_text);
    if(clipboardTextsModelRoot->rowCount() >= maxDataCount)
    {
        clipboardTextsModelRoot->removeRow(maxDataCount - 1);
    }
    clipboardTextsModelRoot->insertRow(0, clipItem);
}
