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

KCClipboardWorker::KCClipboardWorker(QObject *parent) :
    QObject(parent)
{
    clipboardTextsModel=new QStandardItemModel(this);

    systemClipboard=qApp->clipboard();

    connect(systemClipboard,&QClipboard::dataChanged,
            this, &KCClipboardWorker::onSystemClipboardChanged);
}

void KCClipboardWorker::onSystemClipboardChanged()
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

QStandardItemModel *KCClipboardWorker::getClipboardTextsModel() const
{
    return clipboardTextsModel;
}

void KCClipboardWorker::setClipboardTextsModel(QStandardItemModel *value)
{
    clipboardTextsModel = value;
}

QString KCClipboardWorker::getHistoryClipboardText(int itemIndex)
{
    QString newClipData=clipboardTextsModel->item(itemIndex)->data().toString();
    ignoreSignal=true;
    systemClipboard->setText(newClipData);
    return newClipData;
}

int KCClipboardWorker::getMaxDataCount()
{
    return maxDataCount;
}

void KCClipboardWorker::setMaxDataCount(int value)
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

void KCClipboardWorker::addToClipboardStack(QString clipboardText)
{
    QString currentCaption;
    int firstEnterIndex=clipboardText.indexOf("\n");
    if(firstEnterIndex!=-1)
    {
        currentCaption=clipboardText.left(firstEnterIndex).simplified();
        if(currentCaption.isEmpty())
        {
            //This means the first line is empty.
            currentCaption=clipboardText.simplified();
            if(!currentCaption.isEmpty() && currentCaption.length() > 10)
            {
                currentCaption=currentCaption.left(10);
            }
            currentCaption+="...";
        }
        else
        {
            currentCaption+="...";
        }
    }
    else
    {
        currentCaption=clipboardText.simplified();
    }

    QStandardItem *clipItem=new QStandardItem(currentCaption);
    clipItem->setEditable(false);
    int lineCount=5;
    if(clipboardText.count('\n')>lineCount)
    {
        int previewLength=0;
        while(lineCount--)
        {
            previewLength=clipboardText.indexOf('\n', previewLength+1);
        }
        clipItem->setToolTip(clipboardText.left(previewLength)+"...");
    }
    else
    {
        clipItem->setToolTip(clipboardText);
    }
    clipItem->setData(clipboardText);
    int removeItemCount=clipboardTextsModel->rowCount()-maxDataCount+1;
    if(removeItemCount>0)
    {
        clipboardTextsModel->removeRows(maxDataCount-1, removeItemCount);
    }
    clipboardTextsModel->insertRow(0, clipItem);
}

KCClipboard *KCClipboard::instance=nullptr;

KCClipboard *KCClipboard::getInstance()
{
    return instance==nullptr?instance=new KCClipboard:instance;
}

KCClipboard::KCClipboard()
{
    clipboardWorker=new KCClipboardWorker;
    clipboardWorker->moveToThread(&clipboardThread);
    clipboardThread.start();
}

KCClipboard::~KCClipboard()
{
    clipboardThread.quit();
    clipboardThread.wait();
    clipboardWorker->deleteLater();
}

QStandardItemModel *KCClipboard::getClipboardTextsModel() const
{
    return clipboardWorker->getClipboardTextsModel();
}

void KCClipboard::setClipboardTextsModel(QStandardItemModel *value)
{
    clipboardWorker->setClipboardTextsModel(value);
}

QString KCClipboard::getHistoryClipboardText(int itemIndex)
{
    return clipboardWorker->getHistoryClipboardText(itemIndex);
}

int KCClipboard::getMaxDataCount()
{
    return clipboardWorker->getMaxDataCount();
}

void KCClipboard::setMaxDataCount(int value)
{
    clipboardWorker->setMaxDataCount(value);
}
