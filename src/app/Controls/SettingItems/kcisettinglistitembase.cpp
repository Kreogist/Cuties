#include "kcisettinglistitembase.h"

kciSettingListItemBase::kciSettingListItemBase(QWidget *parent) :
    QWidget(parent)
{
    //Set Auto Fill Background.
    setAutoFillBackground(true);
    //Set Palette.
    pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);
    //Set Label.
    Caption=new QLabel(this);
    //Set Default Height.
    setFixedHeight(40);
}
