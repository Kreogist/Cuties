#include "kcsettinglistitemlanguageitem.h"

KCSettingListItemLanguageItem::KCSettingListItemLanguageItem(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    lblLanguageIcon=new QLabel(this);
    MainLayout->addWidget(lblLanguageIcon);

    MainLayout->addWidget(Caption);
    MainLayout->addStretch();

    blnSel=false;
}

void KCSettingListItemLanguageItem::setLanguageImage(QString imgFilePath)
{
    lblLanguageIcon->setPixmap(QPixmap(imgFilePath));
}

void KCSettingListItemLanguageItem::setLanguageName(QString strLanName)
{
    Caption->setText(strLanName);
}
