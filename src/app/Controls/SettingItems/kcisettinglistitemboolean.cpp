#include "kcisettinglistitemboolean.h"

kciSettingListItemBoolean::kciSettingListItemBoolean(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    //Set Layout.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);
    //Set Widget.
    MainLayout->addWidget(Caption);
}
