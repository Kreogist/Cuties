#ifndef KCSETTINGLISTITEMLANGUAGEITEM_H
#define KCSETTINGLISTITEMLANGUAGEITEM_H

#include "kcsettinglistitembase.h"

class KCSettingListItemLanguageItem : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemLanguageItem(QWidget *parent = 0);
    void setLanguageImage(QString imgFilePath);
    void setLanguageName(QString strLanName);

private slots:

private:
    bool blnSel;
    QHBoxLayout *MainLayout;
    QLabel *lblLanguageIcon;
    QLabel *lblLanguageName;
};

#endif // KCSETTINGLISTITEMLANGUAGEITEM_H
