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
