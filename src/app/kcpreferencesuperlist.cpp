
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

    //Set original height
    originalHeight=0;

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
    if(currentItemIndex!=-1)
    {
        superListItems.at(currentItemIndex)->editFinished();
    }
    currentItemIndex=newIndex;
    setFixedHeight(originalHeight+superListItems.at(currentItemIndex)->getExpandFinishedHeight());
}

void KCPreferenceSuperListContent::resetCurrentIndex()
{
    //If there's a select item, finish edit.
    if(currentItemIndex!=-1)
    {
        superListItems.at(currentItemIndex)->editFinished();
        setFixedHeight(originalHeight);
        currentItemIndex=-1;
    }
}

void KCPreferenceSuperListContent::appendTitle(QLabel *newTitleWidget)
{
    superListTitles.append(newTitleWidget);
    superListLayout->addSpacing(5);
    superListLayout->addWidget(newTitleWidget);
    originalHeight=superListLayout->sizeHint().height();
    setFixedHeight(originalHeight);
}

void KCPreferenceSuperListContent::appendItem(KCPreferenceItemBase *newItemWidget)
{
    connect(newItemWidget, SIGNAL(editFocusCapture()),
            superListItemSignalProcessor, SLOT(map()));
    superListItemSignalProcessor->setMapping(newItemWidget, superListItems.count());
    superListItems.append(newItemWidget);
    superListLayout->addWidget(newItemWidget);
    originalHeight=superListLayout->sizeHint().height();
    setFixedHeight(originalHeight);
}

void KCPreferenceSuperListContent::appendStretch()
{
    superListLayout->addStretch();
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

QLabel *KCPreferenceSuperList::addTitle(const QString &titleText)
{
    QLabel *newTitleWidget=new QLabel(contents);
    newTitleWidget->setText(" " + titleText);
    newTitleWidget->setFont(titleFont);
    newTitleWidget->setFixedHeight(30);
    contents->appendTitle(newTitleWidget);
    return newTitleWidget;
}

KCPreferenceItemCombo *KCPreferenceSuperList::addItemCombo(const QString &captionText,
                                                           const QList<QString> &comboItemList,
                                                           int defaultValue)
{
    KCPreferenceItemCombo *newComboItem=new KCPreferenceItemCombo(contents);
    newComboItem->setComboCaptionText(captionText);
    newComboItem->setComboTextList(comboItemList);
    newComboItem->refreshComboText();
    newComboItem->setOriginalValue(defaultValue);
    contents->appendItem(newComboItem);
    return newComboItem;
}

KCPreferenceItemCombo *KCPreferenceSuperList::addItemCombo(KCPreferenceItemCombo *newComboItem)
{
    contents->appendItem(newComboItem);
    return newComboItem;
}

KCPreferenceItemBoolean *KCPreferenceSuperList::addItemBoolean(const QString &captionText,
                                                               bool defaultValue)
{
    KCPreferenceItemBoolean *newBooleanItem=new KCPreferenceItemBoolean(contents);
    newBooleanItem->setBooleanCaptionText(captionText);
    newBooleanItem->setOriginalValue(defaultValue);
    contents->appendItem(newBooleanItem);
    return newBooleanItem;
}

KCPreferenceItemBoolean *KCPreferenceSuperList::addItemBoolean(KCPreferenceItemBoolean *newBooleanItem)
{
    contents->appendItem(newBooleanItem);
    return newBooleanItem;
}

KCPreferenceItemInt *KCPreferenceSuperList::addItemInt(const QString &captionText,
                                                       int defaultValue,
                                                       int maxValue,
                                                       int minValue)
{
    KCPreferenceItemInt *newIntItem=new KCPreferenceItemInt(contents);
    newIntItem->setIntCaptionText(captionText);
    newIntItem->setOriginalValue(defaultValue);
    newIntItem->setMaximumInt(maxValue);
    newIntItem->setMinimumInt(minValue);
    contents->appendItem(newIntItem);
    return newIntItem;
}

KCPreferenceItemInt *KCPreferenceSuperList::addItemInt(KCPreferenceItemInt *newIntItem)
{
    contents->appendItem(newIntItem);
    return newIntItem;
}

KCPreferenceItemBooleanGroup *KCPreferenceSuperList::addItemBooleanGroup(const QString &captionText,
                                                                         bool defaultValue)
{
    KCPreferenceItemBooleanGroup *newBooleanGroupItem=new KCPreferenceItemBooleanGroup(contents);
    newBooleanGroupItem->setBooleanCaptionText(captionText);
    newBooleanGroupItem->setOriginalValue(defaultValue);
    contents->appendItem(newBooleanGroupItem);
    return newBooleanGroupItem;
}

KCPreferenceItemPath *KCPreferenceSuperList::addItemPath(KCPreferenceItemPath *newPathItem)
{
    contents->appendItem(newPathItem);
    return newPathItem;
}

KCPreferenceItemPath *KCPreferenceSuperList::addItemPath(const QString &captionText, QString defaultValue)
{
    KCPreferenceItemPath *newPathItem=new KCPreferenceItemPath(this);
    newPathItem->setPathCaptionText(captionText);
    newPathItem->setOriginalValue(defaultValue);
    contents->appendItem(newPathItem);
    return newPathItem;
}

void KCPreferenceSuperList::addStretch()
{
    contents->appendStretch();
}

void KCPreferenceSuperList::resetCurrentIndex()
{
    contents->resetCurrentIndex();
}

void KCPreferenceSuperList::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    contents->setFixedWidth(event->size().width());
}
