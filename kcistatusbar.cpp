#include "kcistatusbar.h"

kciStatusBar::kciStatusBar(QWidget *parent):
    QStatusBar(parent)
{
    setContentsMargins(0,0,0,0);
    lblCursorPosition=new QLabel(this);


    addPermanentWidget(lblCursorPosition);
}

void kciStatusBar::updateCursorPosition(int LineNum, int ColNum)
{
    if(LineNum>0)
    {
        lblCursorPosition->setText(QString(tr("Line ")) +
                                   QString::number(LineNum) +
                                   QString(tr(", ")) +
                                   QString(tr("Col ")) +
                                   QString::number(ColNum) +
                                   QString(tr(".")));
    }
    else
    {
        lblCursorPosition->setText("");
    }
}
