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

#include <QMouseEvent>
#include <QRect>

#include "kctextblockdata.h"

#include "kcmarkpanel.h"

KCMarkPanel::KCMarkPanel(QWidget *parent) :
    KCPanel(parent)
{
    markPix.load(":/img/image/BreakPoint.png");
    setAutoAdaptWidth(false);
    setAutoFillBackground(true);
    setFixedWidth(25);
    isPressed=false;
}

QPixmap KCMarkPanel::getMarkPix() const
{
    return markPix;
}

void KCMarkPanel::setMarkPix(const QPixmap &value)
{
    markPix = value;
}

void KCMarkPanel::draw(QPainter *painter, QTextBlock *block,
                       int x, int y, int w, int h,
                       bool isCurrentLine)
{
    Q_UNUSED(isCurrentLine);

    KCTextBlockData *data=static_cast<KCTextBlockData *>(block->userData());
    if(data!=NULL)
    {
        markUnit markInfo=data->getMarkInfo();
        QPoint _global(x,y);
        markInfo.rect.setTopLeft(mapToGlobal(_global));
        markInfo.rect.setWidth(w);
        markInfo.rect.setHeight(h);
        data->setMarkInfo(markInfo);

        if(markInfo.marked)
        {
            painter->drawPixmap(x,
                                y - 3,
                                markPix.width(),
                                markPix.height(),
                                markPix);
        }
    }
}

void KCMarkPanel::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=e->globalPos();
    }
}

void KCMarkPanel::mouseReleaseEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        QTextBlock block=getFirstVisiableBlock();
        int lastBlockNumber=getLastVisiableBlockNumber();

        for(; block.blockNumber() <= lastBlockNumber && block.isValid(); block=block.next())
        {
            KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
            if(data !=NULL)
            {
                markUnit _markInfo=data->getMarkInfo();
                if(_markInfo.rect.contains(pressedPos,true))
                {
                    if(_markInfo.rect.contains(e->globalPos(),true))
                    {
                        _markInfo.marked^=1;   //exchange the state
                        data->setMarkInfo(_markInfo);
                        update();
                    }

                    break;  //mouse press in a rect and release in another rect
                }
            }
        }
        isPressed=false;
    }
}
