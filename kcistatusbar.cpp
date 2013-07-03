#include "kcistatusbar.h"

kciStatusBar::kciStatusBar(QWidget *parent):
    QStatusBar(parent)
{
    setContentsMargins(0,0,0,0);
    kscCursorPosition=new kciStatusCursorInfo(this);
    connect(this,SIGNAL(newUpdateCursorPosition(int,int)),
            kscCursorPosition,SLOT(updateCursorPosition(int,int)));
    connect(kscCursorPosition,SIGNAL(ToLineNum(int)),
            this, SIGNAL(ToNewPosition(int)));

    addPermanentWidget(kscCursorPosition);
}

void kciStatusBar::showGotoBar(int currentValue, int MaxValue)
{
    kscCursorPosition->ShowGotoBox(currentValue, MaxValue);
}

void kciStatusBar::updateCursorPosition(int LineNum, int ColNum)
{
    emit newUpdateCursorPosition(LineNum, ColNum);
}
