#include "kcgraphicbuttonok.h"

KCGraphicButtonOK::KCGraphicButtonOK(QWidget *parent) :
    KCGraphicButtonBase(parent)
{
    setNormalGraphic(QPixmap(":/Buttons/image/Buttons/ok_normal.png"));
    setHoverGraphic(QPixmap(":/Buttons/image/Buttons/ok_hover.png"));
    setPressedGraphic(QPixmap(":/Buttons/image/Buttons/ok_normal.png"));
}
