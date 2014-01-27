
#include <QDebug>
#include <QPainter>

#include "kctextblockdata.h"

#include "kcdebugmarkpanel.h"

KCDebugMarkPanel::KCDebugMarkPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    markPix.load(":/img/image/BreakPoint.png");
    debugArrow.load(":/SmartPanel/image/debugarrow.png");
    markPanelHeight=markPix.height();
    setAutoFillBackground(true);
    setFixedWidth(25);
    isPressed=false;
}

void KCDebugMarkPanel::drawContent(int x, int y, int width, int height, QTextBlock block, QTextCursor cursor)
{
    QPainter painter(this);
    KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
    if(data!=NULL)
    {
        markUnit markInfo=data->getMarkInfo();
        QPoint markBegin(x,y);
        markInfo.markRect.setTopLeft(markBegin);
        markInfo.markRect.setWidth(width);
        markInfo.markRect.setHeight(height);
        data->setMarkInfo(markInfo);

        if(markInfo.marked)
        {
            painter.drawPixmap(x,
                                y+(height-markPanelHeight)/2,
                                markPix.width(),
                                markPanelHeight,
                                markPix);
        }
    }

    if(block.blockNumber()==debugCursorLine)
    {
        painter.drawPixmap(x,
                            y+(height-debugArrow.height())/2,
                            debugArrow.width(),
                            debugArrow.height(),
                            debugArrow);
    }
}

void KCDebugMarkPanel::setPanelWidth(int lineNumberPanelWidth)
{
    Q_UNUSED(lineNumberPanelWidth);
    return;
}

void KCDebugMarkPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=event->pos();
    }
}

void KCDebugMarkPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        QTextBlock block=getFirstBlock();
        int lastBlockNumber=getLastBlock().blockNumber();

        for(; block.blockNumber() <= lastBlockNumber && block.isValid(); block=block.next())
        {
            KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
            if(data !=NULL)
            {
                markUnit markInfo=data->getMarkInfo();
                if(markInfo.markRect.contains(pressedPos,true))
                {
                    markInfo.marked^=1;   //exchange the state
                    data->setMarkInfo(markInfo);
                    update();
                    break;  //mouse press in a rect and release in another rect
                }
            }
        }
        isPressed=false;
    }
}
