#include "kcimarkpanel.h"

kciMarkPanel::kciMarkPanel(QWidget *parent) :
    kciPanel(parent)
{
    markPix.load(":/img/image/BreakPoint.png");
    setFixedWidth(32);
    isPressed=false;
}

QPixmap kciMarkPanel::getMarkPix() const
{
    return markPix;
}

void kciMarkPanel::setMarkPix(const QPixmap &value)
{
    markPix = value;
}

void kciMarkPanel::draw(QPainter *painter, QTextBlock *block,
          int x, int y, int w, int h,
          bool isCurrentLine)
{
    Q_UNUSED(isCurrentLine);

    int blockNum=block->blockNumber();

    if(blockNum>=vecMark.size())
        vecMark.resize(blockNum+1);

    QPoint _global(x,y);
    vecMark[blockNum].rect.setTopLeft(mapToGlobal(_global));
    vecMark[blockNum].rect.setWidth(w);
    vecMark[blockNum].rect.setHeight(h);

    if(vecMark[blockNum].marked)
        painter->drawPixmap(x,y,w,h,markPix);
}

void kciMarkPanel::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=e->globalPos();
    }
}

void kciMarkPanel::mouseReleaseEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        int i=vecMark.size();
        while(i--)
        {
            if(vecMark[i].rect.contains(pressedPos,true))
            {
                if(vecMark[i].rect.contains(e->globalPos(),true))
                {
                    vecMark[i].marked^=1;   //exchange the state
                    update();
                }

                break;  //mouse press in a rect and release in another rect
            }
        }
        isPressed=false;
    }
}
