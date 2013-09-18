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

kciClipboard* kciClipboard::instance=nullptr;
int kciClipboard::maxDataCount=10;

kciClipboard::kciClipboard()
{
    clipboardTextsModel=new QStandardItemModel(this);
    clipboardTextsModelRoot=clipboardTextsModel->invisibleRootItem();

    connect(qApp->clipboard(),&QClipboard::dataChanged,
            this,&kciClipboard::onSystemClipboardChanged);
}

kciClipboard* kciClipboard::getInstance()
{
    return instance==nullptr?
                (instance=new kciClipboard):
                instance;
}

void kciClipboard::onSystemClipboardChanged()
{
    QClipboard* _clipboard=qApp->clipboard();
    QString _text=_clipboard->text();

    QStandardItem *clipItem=new QStandardItem(_text);
    clipItem->setEditable(false);
    if(clipboardTextsModelRoot->rowCount() > maxDataCount)
    {
        clipboardTextsModelRoot->removeRow(maxDataCount);
    }
    clipboardTextsModelRoot->insertRow(0, clipItem);
}

QStandardItemModel *kciClipboard::getClipboardTextsModel() const
{
    return clipboardTextsModel;
}

void kciClipboard::setClipboardTextsModel(QStandardItemModel *value)
{
    clipboardTextsModel = value;
}
