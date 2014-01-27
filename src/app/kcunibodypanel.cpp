#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#include "kctextblockdata.h"

#include "kcunibodypanel.h"

KCUnibodyPanel::KCUnibodyPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    setContentsMargins(0,0,0,0);
    foldMark.load(":/SmartPanel/image/folder.png");
    foldEndMark.load(":/SmartPanel/image/folderEnd.png");
    foldedMark.load(":/SmartPanel/image/folded.png");
    compileErrorMark.load(":/SmartPanel/image/compile_error.png");
    foldMarkWidth=foldMark.width();
    foldMarkHeight=foldMark.height();
    errorMarkWidth=compileErrorMark.width();
    errorMarkHeight=compileErrorMark.height();

    setFixedWidth(errorMarkWidth+4);
}

void KCUnibodyPanel::drawContent(int x,
                                 int y,
                                 int width,
                                 int height,
                                 QTextBlock block,
                                 QTextCursor cursor)
{
    Q_UNUSED(x);
    Q_UNUSED(cursor);
    KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
    QPainter painter(this);
    if(data!=NULL)
    {
        QRect currentRect(x, y, width, height);
        data->setCodeLevelRect(currentRect);
        if(data->getHasError())
        {
            painter.drawPixmap((width-errorMarkWidth)/2,
                                y+(height-errorMarkHeight)/2,
                                errorMarkWidth,
                                errorMarkHeight,
                                compileErrorMark);
        }

        if(data->getCodeLevelUp())
        {
            if(data->getHasFolded())
            {
                painter.drawPixmap((width-foldMarkWidth)/2,
                                   y+(height-foldMarkHeight)/2,
                                   foldMarkWidth,
                                   foldMarkHeight,
                                   foldedMark);
            }
            else
            {
                painter.drawPixmap((width-foldMarkWidth)/2,
                                   y+(height-foldMarkHeight)/2,
                                   foldMarkWidth,
                                   foldMarkHeight,
                                   foldMark);
            }
        }
    }
}

void KCUnibodyPanel::setPanelWidth(int lineNumberPanelWidth)
{
    Q_UNUSED(lineNumberPanelWidth);
    return;
}

void KCUnibodyPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        isPressed=true;
        pressedPos=event->pos();
    }
    QWidget::mousePressEvent(event);
}

void KCUnibodyPanel::mouseReleaseEvent(QMouseEvent *event)
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
                QRect currentRect=data->getCodeLevelRect();
                if(currentRect.contains(pressedPos) &&
                   currentRect.contains(event->pos()))
                {
                    if(data->getCodeLevelUp())
                    {
                        if(data->getHasFolded())
                        {
                            //Unfold
                            emit requireUnfoldStartAt(block.blockNumber());
                            data->setHasFolded(false);
                        }
                        else
                        {
                            //Fold
                            emit requireFoldStartAt(block.blockNumber());
                            data->setHasFolded(true);
                        }
                    }
                    break;
                }
            }
        }
        isPressed=false;
    }
    QWidget::mouseReleaseEvent(event);
}
