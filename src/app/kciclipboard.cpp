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
    int index=clipboardTexts.indexOf(_text);
    if(index==-1)
    {
        clipboardTexts.prepend(_text);
    }
    else
    {
        clipboardTexts.removeAt(index);
        clipboardTexts.prepend(_text);
    }

    removeLastTextIfNeeded();
}

void kciClipboard::removeLastTextIfNeeded()
{
    int size=clipboardTexts.size();
    while(size>maxDataCount)
    {
        clipboardTexts.removeLast();
        size--;
    }
}
