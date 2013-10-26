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

#include "kcplaintextbrowser.h"

KCPlainTextBrowser::KCPlainTextBrowser(QWidget *parent) :
    QPlainTextEdit(parent)
{
    connect(verticalScrollBar(),&QScrollBar::valueChanged,
            this,&KCPlainTextBrowser::onScrollValueChanged);

    autoScrollEnabled=true;
    autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                             this,&KCPlainTextBrowser::scrollToEnd);
    setReadOnly(true);
}

void KCPlainTextBrowser::scrollToEnd()
{
    QTextCursor currCursor=textCursor();
    currCursor.movePosition(QTextCursor::End);
    setTextCursor(currCursor);
}

void KCPlainTextBrowser::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    if(autoScrollEnabled)
    {
        scrollToEnd();
    }
}

void KCPlainTextBrowser::onScrollValueChanged(int value)
{
    bool shouldAutoScrollEnabled=(value==verticalScrollBar()->maximum());
    if(autoScrollEnabled==shouldAutoScrollEnabled)
    {
        return ;
    }

    autoScrollEnabled=shouldAutoScrollEnabled;
    if(autoScrollEnabled)
    {
        autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                                 this,&KCPlainTextBrowser::scrollToEnd);
    }
    else
    {
        disconnect(autoScrollHandle);
    }
}
