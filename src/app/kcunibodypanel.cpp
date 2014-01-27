
#include <QPainter>

#include "kctextblockdata.h"

#include "kcunibodypanel.h"

KCUnibodyPanel::KCUnibodyPanel(QWidget *parent) :
    KCTextPanel(parent)
{
    setContentsMargins(0,0,0,0);
    foldMark.load(":/SmartPanel/image/folder.png");
    foldEndMark.load(":/SmartPanel/image/folderEnd.png");
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
    Q_UNUSED(width);
    Q_UNUSED(cursor);
    KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
    QPainter painter(this);
    if(data!=NULL)
    {
        if(data->getHasError())
        {
            painter.drawPixmap((height-errorMarkWidth)/2,
                                y+(height-errorMarkHeight)/2,
                                errorMarkWidth,
                                errorMarkHeight,
                                compileErrorMark);
        }

        if(data->getCodeLevelUp())
        {
            painter.drawPixmap((height-foldMarkWidth)/2,
                                y+(height-foldMarkHeight)/2,
                                foldMarkWidth,
                                foldMarkHeight,
                                foldMark);
        }
    }
}

void KCUnibodyPanel::setPanelWidth(int lineNumberPanelWidth)
{
    Q_UNUSED(lineNumberPanelWidth);
    return;
}
