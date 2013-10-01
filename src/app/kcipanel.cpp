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

#include "kcipanel.h"

kciPanel::kciPanel(QWidget *parent) :
    QWidget(parent),
    e(NULL)
{
    setContentsMargins(0,0,0,0);
    autoWidth=false;
    setMinimumWidth(18);
    setFixedWidth(18);
    setAutoFillBackground(true);
}

bool kciPanel::autoAdaptWidth()
{
    return autoWidth;
}

void kciPanel::setAutoAdaptWidth(bool newValue)
{
    autoWidth=newValue;
}

void kciPanel::setKciTextEditor(KCITextEditor *editor)
{
    if(editor==NULL)
        return ;

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

int kciPanel::getRealLineCount(const QTextBlock &block, const int& offset)
{
    return block.blockNumber() == first ?
                offset:block.lineCount();
}

void kciPanel::paintEvent(QPaintEvent *event)
{
    if(e == NULL||
       e->document() == NULL)
    {
        event->ignore();
        return ;
    }

    QPainter painter(this);

    QBrush brush=painter.background();
    brush.setColor(QColor(0x53,0x53,0x53));
    painter.setBackground(brush);
    painter.fillRect(this->rect(),QColor(0x53,0x53,0x53));

    QFontMetrics fm=e->fontMetrics();

    /*FIXME: It's so ugly. But I can't solve it.I try to find the text layout's
     *       position. But the position of the layout of the QTextBlock is
     *       always be (0,0).
     */

    int line_height = fm.lineSpacing(),
        current_line_num=e->textCursor().block().blockNumber(),
        top=e->verticalScrollBar()->value();

#ifdef Q_OS_MACX
    line_height++;
    int block_top = (top==0)?e->geometry().y() + 5 : 0,
        bottom=e->height()/line_height;
#else
    int block_top = (top==0)?e->geometry().y() + 7 : 3,
        bottom=e->height()/line_height;
#endif

    painter.setFont(e->font());
    QTextBlock block=e->document()->begin();

    if(autoWidth)
    {
        setFixedWidth(fm.width(QString::number(block.document()->blockCount()))+10);
    }

    //find first visiable block
    int line_count;
    for(line_count=0;block.isValid();
        block=block.next())
    {
        line_count+=block.lineCount();
        if(line_count>top)
            break;
    }

    first=block.blockNumber();

    for(;bottom>=0 && block.isValid();
        block=block.next())
    {
        /*If block is the first block, the real line count is (line_count-top).
         *Otherwise the real line count is block.lineCount();
         */
        int block_height=line_height*getRealLineCount(block,line_count-top);
        painter.save();
        this->draw(&painter, &block,
                   0, block_top, width(), block_height,
                   current_line_num==block.blockNumber()?1:0);
        painter.restore();

        block_top += block_height;
        bottom-=getRealLineCount(block,line_count-top);
    }

    last=block.blockNumber();
    while(last == -1)
    {
        block=block.previous();
        last=block.blockNumber();
    }
}

int kciPanel::getFirstVisiableBlockNumber()
{
    return first;
}

int kciPanel::getLastVisiableBlockNumber()
{
    return last;
}
