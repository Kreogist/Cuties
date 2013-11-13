
#include "kcpreferencesuperlist.h"

KCPreferenceSuperListContent::KCPreferenceSuperListContent(QWidget *parent) :
    QWidget(parent)
{
    //Set super layout
    superListLayout=new QVBoxLayout(this);
    superListLayout->setContentsMargins(0,0,0,0);
    superListLayout->setSpacing(0);
    setLayout(superListLayout);
}

void KCPreferenceSuperListContent::appendTitle(QLabel *newTitleWidget)
{
    superListTitles.append(newTitleWidget);
    superListLayout->addSpacing(5);
    superListLayout->addWidget(newTitleWidget);
    setFixedHeight(superListLayout->sizeHint().height());
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

void KCPreferenceSuperList::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    contents->setFixedWidth(event->size().width());
}
