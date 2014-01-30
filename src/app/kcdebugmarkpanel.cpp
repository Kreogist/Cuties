
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
}

void KCDebugMarkPanel::drawContent(int x, int y, int width, int height,
                                   QTextBlock *block, KCTextBlockData *data, QTextCursor cursor)
{
    Q_UNUSED(width);
    Q_UNUSED(cursor);
    QPainter painter(this);
    if(data!=NULL)
    {
        markUnit markInfo=data->getMarkInfo();
        if(markInfo.marked)
        {
            painter.drawPixmap(x,
                               y+(height-markPanelHeight)/2,
                               markPix.width(),
                               markPanelHeight,
                               markPix);
        }
    }

    if(block->blockNumber()==debugCursorLine)
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

void KCDebugMarkPanel::setDebugCursor(int lineNum)
{
    debugCursorLine=lineNum;
    update();
}

void KCDebugMarkPanel::resetDebugCursor()
{
    setDebugCursor(-1);
}

void KCDebugMarkPanel::panelItemClickEvent(QTextBlock *block,
                                             KCTextBlockData *data)
{
    Q_UNUSED(block);
    markUnit markInfo=data->getMarkInfo();
    markInfo.marked^=1;   //exchange the state
    data->setMarkInfo(markInfo);
    update();
}
