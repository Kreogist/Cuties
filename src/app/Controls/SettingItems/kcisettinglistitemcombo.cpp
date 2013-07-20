#include "kcisettinglistitemcombo.h"

kciSettingListItemCombo::kciSettingListItemCombo(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    cboList=new QComboBox(this);
    setFixedWidth(400);

}

void kciSettingListItemCombo::addListItem(const QString &ItemText)
{
    cboList->addItem(ItemText);
}

void kciSettingListItemCombo::clearList()
{
    cboList->clear();
}
