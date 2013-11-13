
#include <QDebug>

#include "kcpreferencepager.h"

KCPreferencePager::KCPreferencePager(QWidget *parent) :
    QWidget(parent)
{
    //Set basic content
    setAutoFillBackground(true);

    //Set palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);
}

void KCPreferencePager::addSuperList(KCPreferenceSuperList *newSuperList)
{
    preferenceSuperLists.append(newSuperList);
}

void KCPreferencePager::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    for(int i=0; i<preferenceSuperLists.count(); i++)
    {
        preferenceSuperLists.at(i)->resize(event->size());
    }
}
