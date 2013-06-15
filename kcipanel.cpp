/*
 *  Copyright 2013 Wang Luming
 *
 *  kcipanel.cpp is part of Kreogist-Cute-IDE.
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
    setFixedWidth(1);
    setAutoFillBackground(true);
}

void kciPanel::setPlainTextEdit(QPlainTextEdit *editor)
{
    if(editor!=NULL)
    {
        if(e!=NULL)
        {
            if((bool)eConnection)
                disconnect(eConnection);
            if((bool)etConnection)
                disconnect(etConnection);
            if((bool)edConnection)
                disconnect(edConnection);
        }

        e=editor;
        eConnection=connect(e->verticalScrollBar(),
                            SIGNAL(valueChanged(int)),
                            this,
                            SLOT(update()));

        etConnection=connect(e,SIGNAL(cursorPositionChanged()),
                             this,SLOT(update()));

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

    int line_hight = e->fontMetrics().lineSpacing(),
        current_line_num=e->textCursor().block().blockNumber();

    int top=e->verticalScrollBar()->value(),
        bottom=e->height()/line_hight + 1;

    int block_top = (top==0)?e->geometry().y() + 7 : 3;

    painter.setFont(e->font());
    QTextBlock block=e->document()->begin();
    setFixedWidth(fm.width(QString::number(block.document()->blockCount()))+10);

    for(;
        block.isValid() && block.isVisible();
        block=block.next())
    {
        if(block.blockNumber() < top)
        {
            continue;
        }

        if(block.blockNumber() > top + bottom)
        {
            break;
        }

        painter.save();
        this->draw(&painter, &block,
                   0, block_top, width(), e->fontMetrics().height(),
                   current_line_num==block.blockNumber()?1:0);
        painter.restore();

        block_top += line_hight;
    }
}
