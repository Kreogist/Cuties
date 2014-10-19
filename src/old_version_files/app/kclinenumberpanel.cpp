
#include <QDebug>
#include <QPainter>

#include "kctextblockdata.h"

#include "kclinenumberpanel.h"

KCLineNumberPanel::KCLineNumberPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    setObjectName("KCLineNumberPanel");
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
    currentWidth=lineNumberPanelWidth;
    if(isVisible() || lineNumberPanelWidth>0)
    {
        setFixedWidth(lineNumberPanelWidth);
    }
    else
    {
        setFixedWidth(0);
    }
}

void KCLineNumberPanel::setVisible(bool visible)
{
    KCTextPanel::setVisible(visible);
    if(visible)
    {
        setFixedWidth(currentWidth);
    }
    else
    {
        setFixedWidth(0);
    }
}

void KCLineNumberPanel::panelItemClickEvent(QTextBlock *block,
        KCTextBlockData *data)
{
    Q_UNUSED(data);
    emit requireSelectBlock(block->blockNumber());
}
