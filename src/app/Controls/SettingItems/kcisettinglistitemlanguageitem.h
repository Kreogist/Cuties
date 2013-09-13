#ifndef KCISETTINGLISTITEMLANGUAGEITEM_H
#define KCISETTINGLISTITEMLANGUAGEITEM_H

#include "kcisettinglistitembase.h"

class kciSettingListItemLanguageItem : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemLanguageItem(QWidget *parent = 0);
    void setLanguageImage(QString imgFilePath);
    void setLanguageName(QString strLanName);

private slots:

private:
    bool blnSel;
    QHBoxLayout *MainLayout;
    QLabel *lblLanguageIcon;
    QLabel *lblLanguageName;
};

#endif // KCISETTINGLISTITEMLANGUAGEITEM_H
