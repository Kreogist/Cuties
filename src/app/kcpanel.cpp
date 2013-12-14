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

#include <QScrollBar>
#include <QFontMetrics>
#include <QDebug>

#include "kctexteditor.h"

#include "kcpanel.h"

KCPanel::KCPanel(QWidget *parent) :
    QWidget(parent),
    e(NULL)
{
    setContentsMargins(0,0,0,0);
    autoWidth=false;
    setMinimumWidth(8);
    setFixedWidth(8);
    setAutoFillBackground(true);
    first=last=0;
}

bool KCPanel::autoAdaptWidth()
{
    return autoWidth;
}

void KCPanel::setAutoAdaptWidth(bool newValue)
{
    autoWidth=newValue;
}

void KCPanel::setTextEditor(KCTextEditor *editor)
{
    if(editor==NULL)
    {
        return ;
    }

    if(e!=NULL)
    {
        connectionHandles.disConnectAll();
    }

    e=editor;

    connectionHandles+=connect(e,SIGNAL(updated()),this,SLOT(update()));

    if(e->document())
        connectionHandles+=connect(e->document()->documentLayout(),
                                   SIGNAL(update()),
                                   this,
                                   SLOT(update()));
}

int KCPanel::getRealLineCount(const QTextBlock &block, const int &offset)
{
    return block.blockNumber() == first ?
           offset:block.lineCount();
}

void KCPanel::paintEvent(QPaintEvent *event)
{
    if(e == NULL||
       e->document() == NULL)
    {
        event->ignore();
        return ;
    }

    QPainter painter(this);

    //TODO: ugly designed
    QBrush brush=painter.background();
    brush.setColor(QColor(0x53,0x53,0x53));
    painter.setBackground(brush);
    painter.fillRect(this->rect(),QColor(0x53,0x53,0x53));

    QFontMetrics fm=e->fontMetrics();
    lineHeight = fm.lineSpacing();
    int currentLineNum=e->textCursor().block().blockNumber(),
        top=e->verticalScrollBar()->value();
    int bottom=e->height()/lineHeight;

    painter.setFont(e->font());
    QTextBlock block=e->document()->begin();

    if(autoWidth)
    {
        setFixedWidth(fm.width(QString::number(block.document()->blockCount()))+2);
    }

    //find first visiable block
    int lineCount;
    for(lineCount=0; block.isValid();
        block=block.next())
    {
        lineCount+=block.lineCount();
        if(lineCount>top)
        {
            break;
        }
    }

    first=block.blockNumber();
    QRectF currentRect;
    int topHint=top==0?4:1;

    for(; bottom>=0 && block.isValid();
        block=block.next())
    {
        /*
         * If block is the first block, the real line count is (line_count-top).
         * Otherwise the real line count is block.lineCount();
         */
        currentRect=e->blockRect(block);
        painter.save();
        this->draw(&painter, &block,
                   0, currentRect.top()+topHint, width(), currentRect.height(),
                   currentLineNum==block.blockNumber()?1:0);
        painter.restore();
        bottom-=getRealLineCount(block,lineCount-top);
    }

    last=block.blockNumber();
    while(last == -1)
    {
        block=block.previous();
        last=block.blockNumber();
    }
}

int KCPanel::getFirstVisiableBlockNumber()
{
    return first;
}

int KCPanel::getLastVisiableBlockNumber()
{
    return last;
}

QTextBlock KCPanel::getFirstVisiableBlock()
{
    return e->document()->findBlockByNumber(first);
}

QTextBlock KCPanel::getLastVisiableBlock()
{
    Q_ASSERT(last != -1);
    return e->document()->findBlockByNumber(last);
}
