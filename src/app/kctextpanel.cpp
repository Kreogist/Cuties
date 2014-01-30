
#include <QTextBlock>
#include <QMouseEvent>

#include "kctextblockdata.h"
#include "kctextpanel.h"

KCTextPanel::KCTextPanel(QWidget *parent) :
    QWidget(parent)
{
    ;
}

void KCTextPanel::paintEvent(QPaintEvent *event)
{
    emit requireRepaintPanel(this, event);
}

void KCTextPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=event->pos();
    }
    QWidget::mousePressEvent(event);
}

void KCTextPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        QTextBlock block=getFirstBlock();
        KCTextBlockData *data;
        int lastBlockNumber=getLastBlock().blockNumber();

        for(; block.blockNumber() <= lastBlockNumber && block.isValid(); block=block.next())
        {
            data=static_cast<KCTextBlockData *>(block.userData());
            if(block.isVisible() && data!=NULL)
            {
                QRect mouseDetectRect=data->getRect();
                if(mouseDetectRect.contains(pressedPos) &&
                   mouseDetectRect.contains(event->pos()))
                {
                    mouseClickEventRaised(&block, data);
                    break;
                }
            }
        }
        isPressed=false;
    }
    QWidget::mouseReleaseEvent(event);
}

void KCTextPanel::mouseClickEventRaised(QTextBlock *block,
                                        KCTextBlockData *data)
{
    Q_UNUSED(block);
    Q_UNUSED(data);
}

QTextBlock KCTextPanel::getLastBlock() const
{
    return lastBlock;
}

void KCTextPanel::setLastBlock(const QTextBlock &value)
{
    lastBlock = value;
}

QTextBlock KCTextPanel::getFirstBlock() const
{
    return firstBlock;
}

void KCTextPanel::setFirstBlock(const QTextBlock &value)
{
    firstBlock = value;
}
