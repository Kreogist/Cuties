
#include "kcpreferencesuperlist.h"

KCPreferenceSuperListContent::KCPreferenceSuperListContent(QWidget *parent) :
    QWidget(parent)
{
    //Set widget size policy
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFixedSize(500,500);

    //Set super layout
    superListLayout=new QVBoxLayout(this);
    superListLayout->setContentsMargins(0,0,0,0);
    superListLayout->setSpacing(0);
    setLayout(superListLayout);
}

QVBoxLayout *KCPreferenceSuperListContent::getSuperListLayout()
{
    return superListLayout;
}

QList<QLabel *> KCPreferenceSuperListContent::getSuperListTitles()
{
    return superListTitles;
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
    contents->getSuperListTitles().append(newTitleWidget);
    contents->getSuperListLayout()->addSpacing(5);
    contents->getSuperListLayout()->addWidget(newTitleWidget);
}
