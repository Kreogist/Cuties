/*
 *
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

#include <QClipboard>
#include <QApplication>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>

#include "kcclipboard.h"

KCClipboard *KCClipboard::instance=nullptr;

KCClipboard::KCClipboard()
{
    clipboardTextsModel=new QStandardItemModel(this);

    systemClipboard=qApp->clipboard();

    connect(systemClipboard,&QClipboard::dataChanged,
            this, &KCClipboard::onSystemClipboardChanged);
}

KCClipboard *KCClipboard::getInstance()
{
    return instance==nullptr?instance=new KCClipboard:instance;
}

void KCClipboard::onSystemClipboardChanged()
{
    if(!ignoreSignal)
    {
        if(!systemClipboard->text().isEmpty())
        {
            addToClipboardStack(systemClipboard->text());
        }
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
    QString newClipData=clipboardTextsModel->item(itemIndex)->data().toString();
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
        int removeItemCount=clipboardTextsModel->rowCount()-value;
        if(removeItemCount>0)
        {
            clipboardTextsModel->removeRows(value, removeItemCount);
        }
    }
    maxDataCount = value;
}

void KCClipboard::addToClipboardStack(QString _text)
{
    QString currentCaption;
    int firstEnterIndex=_text.indexOf("\n");
    if(firstEnterIndex!=-1)
    {
        currentCaption=_text.left(firstEnterIndex).simplified();
        if(currentCaption.isEmpty())
        {
            //This means the first line is empty.
            currentCaption=_text.simplified();
            if(!currentCaption.isEmpty() && currentCaption.length() > 10)
            {
                currentCaption=currentCaption.left(10);
            }
            currentCaption+=+"...";
        }
        else
        {
            currentCaption+=+"...";
        }
    }
    else
    {
        currentCaption=_text.simplified();
    }

    QStandardItem *clipItem=new QStandardItem(currentCaption);
    clipItem->setEditable(false);
    clipItem->setToolTip(_text);
    clipItem->setData(_text);
    int removeItemCount=clipboardTextsModel->rowCount()-maxDataCount+1;
    if(removeItemCount>0)
    {
        clipboardTextsModel->removeRows(maxDataCount-1, removeItemCount);
    }
    clipboardTextsModel->insertRow(0, clipItem);
}
