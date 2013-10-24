#include "kcsettinglistitemlanguageitem.h"

KCSettingListItemLanguageItem::KCSettingListItemLanguageItem(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    setAutoFillBackground(true);
    pal=palette();

    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    languageIcon=new QLabel(this);
    mainLayout->addWidget(languageIcon);

    mainLayout->addWidget(captionText);
    mainLayout->addStretch();

    languageSelected=false;
}

void KCSettingListItemLanguageItem::setCheck(bool value)
{
    languageSelected=value;
    if(value)
    {
        pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,255));
        setPalette(pal);
    }
    else
    {
        pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,0));
        setPalette(pal);
    }
}

void KCSettingListItemLanguageItem::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    emit languageSelect();
}

void KCSettingListItemLanguageItem::setLanguageImage(QString imgFilePath)
{
    languageIcon->setPixmap(QPixmap(imgFilePath));
}

void KCSettingListItemLanguageItem::setLanguageName(QString strLanName)
{
    captionText->setText(strLanName);
}

void KCSettingListItemLanguageItem::enterEvent(QEvent *e)
{
    if(!languageSelected)
    {
        KCSettingListItemBase::enterEvent(e);
        return;
    }
    QWidget::enterEvent(e);
}

void KCSettingListItemLanguageItem::leaveEvent(QEvent *e)
{
    if(!languageSelected)
    {
        KCSettingListItemBase::leaveEvent(e);
        return;
    }
    QWidget::leaveEvent(e);
}
