#include "kcsettingcontrollineedit.h"

KCSettingControlLineEdit::KCSettingControlLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void KCSettingControlLineEdit::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QLineEdit::mousePressEvent(event);
}
