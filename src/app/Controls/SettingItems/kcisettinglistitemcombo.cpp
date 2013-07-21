#include "kcisettinglistitemcombo.h"

kciSettingListItemCombo::kciSettingListItemCombo(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    cboList=new QComboBox(this);
    MainLayout->addWidget(Caption);
    MainLayout->addWidget(cboList);
}

void kciSettingListItemCombo::addListItem(const QString &ItemText)
{
    cboList->addItem(ItemText);
}

void kciSettingListItemCombo::clearList()
{
    cboList->clear();
}
