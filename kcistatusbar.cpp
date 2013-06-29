#include "kcistatusbar.h"

kciStatusBar::kciStatusBar(QWidget *parent):
    QStatusBar(parent)
{
    setContentsMargins(0,0,0,0);
    lblCursorPosition=new QLabel(this);

    addWidget(lblCursorPosition);
}

void kciStatusBar::updateCursorPosition(int LineNum, int ColNum)
{
    lblCursorPosition->setText(QString(tr("Line: ")) +
            QString::number(LineNum) + " " +
            QString(tr("Col: ")) +
            QString::number(ColNum));
}
