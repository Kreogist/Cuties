
#include <QDebug>
#include <QPainter>

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
                                    QTextBlock block,
                                    QTextCursor cursor)
{
    QPainter painter(this);
    bool isCurrentLine=cursor.blockNumber()==block.blockNumber();
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
    painter.drawText(x, y, width, height,
                     Qt::AlignRight, QString::number(block.blockNumber() + 1));
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
