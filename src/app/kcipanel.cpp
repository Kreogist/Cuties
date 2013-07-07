/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcipanel.h"

kciPanel::kciPanel(QWidget *parent) :
    QWidget(parent),
    e(NULL)
{
    setContentsMargins(0,0,0,0);
    setFixedWidth(1);
    setAutoFillBackground(true);
}

void kciPanel::setKciCodeEditor(kciCodeEditor *editor)
{
    if(editor!=NULL)
    {
        if(e!=NULL)
        {
            if((bool)etConnection)
                disconnect(etConnection);
            if((bool)edConnection)
                disconnect(edConnection);
        }

        e=editor;

        etConnection=connect(e,SIGNAL(updated()),this,SLOT(update()));

        if(e->document())
            edConnection=connect(e->document()->documentLayout(),
                                 SIGNAL(update()),
                                 this,
                                 SLOT(update()));
    }
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

    setFont(e->font());
    QFont font(e->font());
    QFontMetrics fm(font);

    /*FIXME: It's so ugly. But I can't solve it.I try to find the text layout's
     *       position. But the position of the layout of the QTextBlock is
     *       always be (0,0).
     */

    int line_height = e->fontMetrics().lineSpacing(),
        current_line_num=e->textCursor().block().blockNumber();

    int top=e->verticalScrollBar()->value();

    int block_top = (top==0)?e->geometry().y() + 7 : 3,
        bottom=e->height()/line_height;

    painter.setFont(e->font());
    QTextBlock block=e->document()->begin();
    setFixedWidth(fm.width(QString::number(block.document()->blockCount()))+10);

    //find first visiable block
    for(int line_count=0;block.isValid();
        block=block.next())
    {
        line_count+=block.lineCount();
        if(line_count>top)
            break;
    }

    for(;bottom>=0 && block.isValid();
        block=block.next())
    {
        int block_height=line_height*block.lineCount();
        painter.save();
        this->draw(&painter, &block,
                   0, block_top, width(), block_height,
                   current_line_num==block.blockNumber()?1:0);
        painter.restore();

        block_top += block_height;
        bottom-=block.lineCount();
    }
}
