
#include <QDebug>

#include "kcpreferencesuperlist.h"

KCPreferenceSuperListContent::KCPreferenceSuperListContent(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);

    //Set super layout
    superListLayout=new QVBoxLayout(this);
    superListLayout->setContentsMargins(0,0,0,0);
    superListLayout->setSpacing(0);
    setLayout(superListLayout);

    //Set current index
    currentItemIndex=-1;

    //Set item signal mapper
    superListItemSignalProcessor=new QSignalMapper(this);
    connect(superListItemSignalProcessor, SIGNAL(mapped(int)),
            this, SLOT(transferCurrentIndex(int)));
}

void KCPreferenceSuperListContent::transferCurrentIndex(int newIndex)
{
    if(currentItemIndex==newIndex)
    {
        return;
    }
    int lastItemHeight=0;
    if(currentItemIndex!=-1)
    {
        superListItems.at(currentItemIndex)->editFinished();
        lastItemHeight=superListItems.at(currentItemIndex)->getExpandFinishedHeight();
    }
    currentItemIndex=newIndex;
    setFixedHeight(size().height()+superListItems.at(currentItemIndex)->getExpandFinishedHeight()-lastItemHeight);
}

void KCPreferenceSuperListContent::appendTitle(QLabel *newTitleWidget)
{
    superListTitles.append(newTitleWidget);
    superListLayout->addSpacing(5);
    superListLayout->addWidget(newTitleWidget);
    setFixedHeight(superListLayout->sizeHint().height());
}

void KCPreferenceSuperListContent::appendItem(KCPreferenceItemBase *newItemWidget)
{
    connect(newItemWidget, SIGNAL(editFocusCapture()),
            superListItemSignalProcessor, SLOT(map()));
    superListItemSignalProcessor->setMapping(newItemWidget, superListItems.count());
    superListItems.append(newItemWidget);
    superListLayout->addWidget(newItemWidget);
    setFixedHeight(superListLayout->sizeHint().height());
}

void KCPreferenceSuperListContent::appendStretch()
{
    superListLayout->addStretch();
}

QList<QLabel *> KCPreferenceSuperListContent::getSuperListTitles() const
{
    return superListTitles;
}

QList<KCPreferenceItemBase *> KCPreferenceSuperListContent::getSuperListItems() const
{
    return superListItems;
}

KCPreferenceSuperList::KCPreferenceSuperList(QWidget *parent) :
    QScrollArea(parent)
{
    //Set properties.
    setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);

    //Set contents widget
    contents=new KCPreferenceSuperListContent(this);
    setWidget(contents);

    //Set font
    titleFont=this->font();
    titleFont.setPixelSize(20);
}

void KCPreferenceSuperList::addTitle(const QString &titleText)
{
    QLabel *newTitleWidget=new QLabel(contents);
    newTitleWidget->setText(" " + titleText);
    newTitleWidget->setFont(titleFont);
    newTitleWidget->setFixedHeight(30);
    contents->appendTitle(newTitleWidget);
}

void KCPreferenceSuperList::addItemCombo(const QString &captionText,
                                         const QList<QString> &comboItemList,
                                         int defaultValue)
{
    KCPreferenceItemCombo *newComboItem=new KCPreferenceItemCombo(contents);
    newComboItem->setComboCaptionText(captionText);
    newComboItem->setComboTextList(comboItemList);
    newComboItem->refreshComboText();
    newComboItem->setOriginalValue(defaultValue);
    contents->appendItem(newComboItem);
}

void KCPreferenceSuperList::addItemBoolean(const QString &captionText,
                                           bool defaultValue)
{
    KCPreferenceItemBoolean *newBooleanItem=new KCPreferenceItemBoolean(contents);
    newBooleanItem->setBooleanCaptionText(captionText);
    newBooleanItem->setOriginalValue(defaultValue);
    contents->appendItem(newBooleanItem);
}

void KCPreferenceSuperList::addItemInt(const QString &captionText,
                                       int defaultValue)
{
    KCPreferenceItemInt *newIntItem=new KCPreferenceItemInt(contents);
    newIntItem->setIntCaptionText(captionText);
    newIntItem->setOriginalValue(defaultValue);
    contents->appendItem(newIntItem);
}

void KCPreferenceSuperList::addStretch()
{
    contents->appendStretch();
}

void KCPreferenceSuperList::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    contents->setFixedWidth(event->size().width());
}
