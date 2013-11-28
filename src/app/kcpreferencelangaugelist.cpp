#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QSignalMapper>

#include "kcpreferencelangaugelist.h"

KCPreferenceLangaugeListItem::KCPreferenceLangaugeListItem(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setFixedHeight(36);

    //Get palette
    backgroundColor=QColor(0xf7,0xcf,0x3d,0);
    pal=palette();
    setBackgroundAlpha(0);

    //Set layout
    QHBoxLayout *languageItemLayout=new QHBoxLayout(this);
    languageItemLayout->setContentsMargins(5,0,5,0);
    languageItemLayout->setSpacing(5);
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

void KCPreferenceLangaugeListItem::setBackgroundAlpha(int newAlpha)
{
    backgroundColor.setAlpha(newAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

void KCPreferenceLangaugeListItem::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    setBackgroundAlpha(255);
}

void KCPreferenceLangaugeListItem::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    setBackgroundAlpha(0);
}

void KCPreferenceLangaugeListItem::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    emit requireChangeLanguage();
}

KCPreferenceLangaugeList::KCPreferenceLangaugeList(QWidget *parent) :
    QScrollArea(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    //Set signal mapper
    QSignalMapper *languageChangeMapper=new QSignalMapper(this);

    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    //Set content widget
    languageContents=new QWidget(this);
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
        connect(languageItems.at(i), SIGNAL(requireChangeLanguage()),
                languageChangeMapper, SLOT(map()));
        languageChangeMapper->setMapping(languageItems.at(i), i);
        languageListLayout->addWidget(languageItems.at(i));
    }
    connect(languageChangeMapper, SIGNAL(mapped(int)),
            this, SIGNAL(requireChangeLanguage(int)));
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

void KCPreferenceLangaugeList::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    if(verticalScrollBar()->isVisible())
    {
        languageContents->setFixedWidth(width() - verticalScrollBar()->width()-2);
    }
    else
    {
        languageContents->setFixedWidth(width()-2);
    }
}
