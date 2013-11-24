#include <QHBoxLayout>

#include "kcpreferencelangaugelist.h"

KCPreferenceLangaugeListItem::KCPreferenceLangaugeListItem(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *languageItemLayout=new QHBoxLayout(this);
    languageItemLayout->setContentsMargins(0,0,0,0);
    languageItemLayout->setSpacing(0);
    setLayout(languageItemLayout);

    languageIcon=new QLabel(this);
    languageItemLayout->addWidget(languageIcon);

    languageName=new QLabel(this);
    languageItemLayout->addWidget(languageName);

    languageItemLayout->addStretch();
}

void KCPreferenceLangaugeListItem::setLanguageIcon(const QString &iconPath)
{
    languageIcon->setPixmap(QPixmap(iconPath));
}

void KCPreferenceLangaugeListItem::setLanguageName(const QString &captionText)
{
    languageName->setText(captionText);
}

KCPreferenceLangaugeList::KCPreferenceLangaugeList(QWidget *parent) :
    QWidget(parent)
{
    KCPreferenceLangaugeListItem *test=new KCPreferenceLangaugeListItem(this);
}

