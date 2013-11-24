#include <QHBoxLayout>
#include <QVBoxLayout>

#include "kcpreferencelangaugelist.h"

KCPreferenceLangaugeListItem::KCPreferenceLangaugeListItem(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *languageItemLayout=new QHBoxLayout(this);
    languageItemLayout->setContentsMargins(0,0,0,0);
    languageItemLayout->setSpacing(0);
    setLayout(languageItemLayout);

    languageIcon=new QLabel(this);
    languageIcon->setFixedSize(32,32);
    languageIcon->setScaledContents(true);
    languageItemLayout->addWidget(languageIcon);

    languageName=new QLabel(this);
    languageItemLayout->addWidget(languageName);

    languageItemLayout->addStretch();
}

void KCPreferenceLangaugeListItem::setLanguageIcon(const QPixmap &languagePixmap)
{
    languageIcon->setPixmap(languagePixmap);
}

void KCPreferenceLangaugeListItem::setLanguageName(const QString &captionText)
{
    languageName->setText(captionText);
}

KCPreferenceLangaugeList::KCPreferenceLangaugeList(QWidget *parent) :
    QScrollArea(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    //Set content widget
    QWidget *languageContents=new QWidget(this);
    languageContents->setContentsMargins(0,0,0,0);
    setWidget(languageContents);

    //Set layout
    QVBoxLayout *languageListLayout=new QVBoxLayout(languageContents);
    languageListLayout->setContentsMargins(0,0,0,0);
    languageListLayout->setSpacing(0);
    languageContents->setLayout(languageListLayout);

    instance=KCLanguageConfigure::getInstance();
    int languageCount=instance->getLanguageList().count();
    for(int i=0;i<languageCount;i++)
    {
        languageItems.append(addLanguageItem(instance->getLanguageCaption().at(i),
                                             instance->getLanguageFileIcon().at(i)));
        languageListLayout->addWidget(languageItems.at(i));
    }
    languageListLayout->addStretch();
    languageContents->setFixedSize(languageContents->sizeHint());
}

KCPreferenceLangaugeListItem *KCPreferenceLangaugeList::addLanguageItem(const QString &languageName,
                                                                        const QPixmap &languageIcon)
{
    KCPreferenceLangaugeListItem *newLanguageItem=new KCPreferenceLangaugeListItem(this);
    newLanguageItem->setLanguageName(languageName);
    newLanguageItem->setLanguageIcon(languageIcon);
    return newLanguageItem;
}

