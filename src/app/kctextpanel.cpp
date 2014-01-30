/*
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

#include <QDebug>

#include <QTextBlock>
#include <QMouseEvent>

#include "kctextblockdata.h"
#include "kctextpanel.h"

/*!
 * \brief Constructs a KCTextPanel with the given parent and the specified
 * widget flags.
 * \param parent Specifies the parent QWidget.
 */
KCTextPanel::KCTextPanel(QWidget *parent) :
    QWidget(parent)
{
    ;
}

/*!
 * \brief The paint event of KCTextPanel. Panel will emit a signal to require
 * paint the panel.
 * \param event The paint event of the current panel.
 */
void KCTextPanel::paintEvent(QPaintEvent *event)
{
    emit requireRepaintPanel(this, event);
}

/*!
 * \brief This function is used to save position then the mouse press inside the
 * panel.
 * \param event The mouse press event of the current panel.
 */
void KCTextPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        isPressed=true;
    }
    QWidget::mousePressEvent(event);
}

/*!
 * \brief This function is used to detect when the mouse key was release and the
 * mouse pointer is still at the postion which when mousePressEvent() save. If
 * we find out a block contains the mouse pointer, called the
 * mouseClickEventRaised() and tell the function the block and the data.
 *
 * The reason to tell the mouseClickEventRaised() the block and block data is
 * only for speed up.
 * \param event The mouse release event of the current panel.
 */
void KCTextPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        QTextBlock block=getFirstBlock();
        KCTextBlockData *data;
        int lastBlockNumber=getLastBlock().blockNumber();

        qDebug()<<block.blockNumber()<<lastBlockNumber;
        for(; block.blockNumber() <= lastBlockNumber && block.isValid(); block=block.next())
        {
            qDebug()<<"Here?!!!!";
            if(!block.isVisible())
            {
                continue;
            }
            data=static_cast<KCTextBlockData *>(block.userData());
            qDebug()<<(data==NULL);
            if(data!=NULL)
            {
                QRect mouseDetectRect=data->getRect();
                qDebug()<<mouseDetectRect<<event->pos();
                if(mouseDetectRect.contains(event->pos()))
                {
                    panelItemClickEvent(&block, data);
                    break;
                }
            }
        }
        isPressed=false;
    }
    QWidget::mouseReleaseEvent(event);
}

/*!
 * \brief This function is set to process the things when the mouse click a item
 * inside the panel.
 * \param block The text editor's block of the position confirm.
 * \param data The block data of the block, this arg is only for speed up.
 */
void KCTextPanel::panelItemClickEvent(QTextBlock *block,
                                      KCTextBlockData *data)
{
    Q_UNUSED(block);
    Q_UNUSED(data);
}

/*!
 * \brief This will get the last visible block of current panel.
 */
QTextBlock KCTextPanel::getLastBlock() const
{
    return lastBlock;
}

/*!
 * \brief This will set the last visible block of current panel.
 * \param value The last block of the panel.
 */
void KCTextPanel::setLastBlock(const QTextBlock &value)
{
    lastBlock = value;
}

/*!
 * \brief This will get the first visible block of current panel.
 */
QTextBlock KCTextPanel::getFirstBlock() const
{
    return firstBlock;
}

/*!
 * \brief This will set the fisrt visible block of current panel.
 * \param value The first block of the panel.
 */
void KCTextPanel::setFirstBlock(const QTextBlock &value)
{
    firstBlock = value;
}
