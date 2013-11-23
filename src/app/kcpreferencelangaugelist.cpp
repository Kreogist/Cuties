#include <QHBoxLayout>

#include "kcpreferencelangaugelist.h"

KCPreferenceLangaugeListItem::KCPreferenceLangaugeListItem(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *languageItemLayout=new QHBoxLayout(this);
    languageItemLayout->setContentsMargins(0,0,0,0);
    languageItemLayout->setSpacing(0);
    setLayout(languageItemLayout);
    ;
}

KCPreferenceLangaugeList::KCPreferenceLangaugeList(QWidget *parent) :
    QWidget(parent)
{
    KCPreferenceLangaugeListItem *test=new KCPreferenceLangaugeListItem(this);
}

