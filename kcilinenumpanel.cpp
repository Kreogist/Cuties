#include "kcilinenumpanel.h"

kciLinenumPanel::kciLinenumPanel(QWidget *parent) :
    kciPanel(parent)
{
    textColor.setRgb(255,255,255,200);
}

void kciLinenumPanel::draw(QPainter *painter, QTextBlock *block,
                           int x, int y, int w, int h,
                           bool isCurrentLine)
{
    if(isCurrentLine)
    {
        QFont font=painter->font();
        font.setBold(true);
        painter->setFont(font);

        textColor.setAlpha(255);
    }

    QPen pen(painter->pen ());
    pen.setColor(textColor);
    painter->setPen(pen);

    painter->drawText(x, y, w, h,
            Qt::AlignRight |  Qt::AlignTop,
            QString::number(block->blockNumber()+1));

    if(isCurrentLine)
    {
        QFont font=painter->font();
        font.setBold(false);
        painter->setFont(font);

        textColor.setAlpha(200);
    }

}
