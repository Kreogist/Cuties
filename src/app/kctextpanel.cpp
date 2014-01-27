#include "kctextpanel.h"

KCTextPanel::KCTextPanel(QWidget *parent) :
    QWidget(parent)
{
    ;
}

void KCTextPanel::paintEvent(QPaintEvent *event)
{
    emit requireRepaintLineNumber(this, event);
}

QTextBlock KCTextPanel::getLastBlock() const
{
    return lastBlock;
}

void KCTextPanel::setLastBlock(const QTextBlock &value)
{
    lastBlock = value;
}

QTextBlock KCTextPanel::getFirstBlock() const
{
    return firstBlock;
}

void KCTextPanel::setFirstBlock(const QTextBlock &value)
{
    firstBlock = value;
}
