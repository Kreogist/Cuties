#include <QDebug>
#include <QPainter>

#include "kctextblockdata.h"

#include "kcunibodypanel.h"

KCUnibodyPanel::KCUnibodyPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    setObjectName("KCUnibodyPanel");
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
                                 QTextBlock *block,
                                 KCTextBlockData *data,
                                 QTextCursor cursor)
{
    Q_UNUSED(x);
    Q_UNUSED(block)
    Q_UNUSED(cursor);
    if(data!=NULL)
    {
        QPainter painter(this);
        codeLevelUnit codeLevelInfo=data->getCodeLevelInfo();

        if(codeLevelInfo.hasError)
        {
            painter.drawPixmap((width-errorMarkWidth)/2,
                               y+(height-errorMarkHeight)/2,
                               errorMarkWidth,
                               errorMarkHeight,
                               compileErrorMark);
        }
        if(codeLevelInfo.codeLevelUp)
        {
            if(codeLevelInfo.hasFolded)
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

void KCUnibodyPanel::panelItemClickEvent(QTextBlock *block,
        KCTextBlockData *data)
{
    codeLevelUnit codeLevelInfo=data->getCodeLevelInfo();
    if(codeLevelInfo.codeLevelUp)
    {
        if(codeLevelInfo.hasFolded)
        {
            //Unfold
            emit requireUnfoldStartAt(block->blockNumber());
            emit requireUpdateAllPanel();
            codeLevelInfo.hasFolded=false;
        }
        else
        {
            //Fold
            emit requireFoldStartAt(block->blockNumber());
            emit requireUpdateAllPanel();
            codeLevelInfo.hasFolded=true;
        }
        data->setCodeLevelInfo(codeLevelInfo);
    }
}
