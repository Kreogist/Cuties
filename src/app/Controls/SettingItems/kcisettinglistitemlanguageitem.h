#ifndef KCISETTINGLISTITEMLANGUAGEITEM_H
#define KCISETTINGLISTITEMLANGUAGEITEM_H

#include "kcisettinglistitembase.h"

class kciSettingListItemLanguageItem : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemLanguageItem(QWidget *parent = 0);

private slots:

private:
    bool blnSel;
    QHBoxLayout *MainLayout;
    QLabel *lblLanguageIcon;
};

#endif // KCISETTINGLISTITEMLANGUAGEITEM_H
