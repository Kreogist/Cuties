
#include <QDebug>
#include <QPainter>

#include "kctextblockdata.h"

#include "kclinenumberpanel.h"

KCLineNumberPanel::KCLineNumberPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    textColor.setRgb(120,120,120);
}

void KCLineNumberPanel::drawContent(int x,
                                    int y,
                                    int width,
                                    int height,
                                    QTextBlock *block,
                                    KCTextBlockData *data,
                                    QTextCursor cursor)
{
    Q_UNUSED(data);
    QPainter painter(this);
    bool isCurrentLine=cursor.blockNumber()==block->blockNumber();
    if(isCurrentLine)
    {
        QFont font=painter.font();
        font.setBold(true);
        painter.setFont(font);

        textColor.setRgb(255,255,255);
    }
    QPen pen(painter.pen());
    pen.setColor(textColor);
    painter.setPen(pen);
    painter.drawText(x, y+(height-fontMetrics().height())/2, width, height,
                     Qt::AlignRight, QString::number(block->blockNumber() + 1));
    if(isCurrentLine)
    {
        QFont font=painter.font();
        font.setBold(false);
        painter.setFont(font);

        textColor.setRgb(120,120,120);
    }
}

void KCLineNumberPanel::setPanelWidth(int lineNumberPanelWidth)
{
    setFixedWidth(lineNumberPanelWidth);
}

void KCLineNumberPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=event->pos();
    }
    QWidget::mousePressEvent(event);
}

void KCLineNumberPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        QTextBlock block=getFirstBlock();
        int lastBlockNumber=getLastBlock().blockNumber();

        for(; block.blockNumber() <= lastBlockNumber && block.isValid(); block=block.next())
        {
            KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
            if(block.isVisible() && data!=NULL)
            {
                QRect lineNumberRect=data->getRect();
                if(lineNumberRect.contains(pressedPos) &&
                   lineNumberRect.contains(event->pos()))
                {
                    emit requireSelectLine(block.blockNumber());
                    break;
                }
            }
        }
        isPressed=false;
    }
    QWidget::mouseReleaseEvent(event);
}
