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

#include "kciclipboard.h"

kciClipboard *kciClipboard::instance=nullptr;

kciClipboard::kciClipboard()
{
    clipboardTextsModel=new QStandardItemModel(this);
    clipboardTextsModelRoot=clipboardTextsModel->invisibleRootItem();

    ignoreSignal=false;
    maxDataCount=10;

    connect(qApp->clipboard(),&QClipboard::dataChanged,
            this,&kciClipboard::onSystemClipboardChanged);
}

kciClipboard *kciClipboard::getInstance()
{
    return instance==nullptr?
           (instance=new kciClipboard):
           instance;
}

void kciClipboard::onSystemClipboardChanged()
{
    if(!ignoreSignal)
    {
        QClipboard *_clipboard=qApp->clipboard();
        QString _text=_clipboard->text();
        QString _caption;
        int firstNextLineChar=_text.indexOf("\n");
        if(firstNextLineChar!=-1)
        {
            _caption=_text.left(firstNextLineChar) + "...";
        }
        else
        {
            _caption=_text;
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
    else
    {
        ignoreSignal=false;
    }
}

QStandardItemModel *kciClipboard::getClipboardTextsModel() const
{
    return clipboardTextsModel;
}

void kciClipboard::setClipboardTextsModel(QStandardItemModel *value)
{
    clipboardTextsModel = value;
}

QString kciClipboard::getHistoryClipboardText(int ItemID)
{
    QString newClipData=clipboardTextsModel->item(ItemID)->toolTip();
    ignoreSignal=true;
    qApp->clipboard()->setText(newClipData);
    return newClipData;
}

int kciClipboard::getMaxDataCount()
{
    return maxDataCount;
}

void kciClipboard::setMaxDataCount(int value)
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
