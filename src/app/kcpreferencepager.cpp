
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

    //Set current page index
    currentPageIndex=-1;
}

void KCPreferencePager::addSuperList(KCPreferenceSuperList *newSuperList)
{
    newSuperList->setEnabled(false);
    newSuperList->setVisible(false);
    preferenceSuperLists.append(newSuperList);
}

void KCPreferencePager::initPager()
{
    currentPageIndex=0;
    setPageVisible(currentPageIndex, true);
}

void KCPreferencePager::setPageVisible(int pageIndex, bool visible)
{
    preferenceSuperLists.at(pageIndex)->setVisible(visible);
    preferenceSuperLists.at(pageIndex)->setEnabled(visible);
}

void KCPreferencePager::switchToPage(int pageIndex)
{
    preferenceSuperLists.at(currentPageIndex)->resetCurrentIndex();
    QParallelAnimationGroup *moveAnimationGroup=new QParallelAnimationGroup(this);
    QPropertyAnimation *throwLastPage=new QPropertyAnimation(preferenceSuperLists.at(currentPageIndex), "geometry", this);
    QPropertyAnimation *putCurrentPage=new QPropertyAnimation(preferenceSuperLists.at(pageIndex), "geometry", this);
    throwLastPage->setEasingCurve(QEasingCurve::OutCubic);
    putCurrentPage->setEasingCurve(QEasingCurve::OutCubic);
    throwLastPage->setDuration(200);
    putCurrentPage->setDuration(200);
    QRect currentPosition=preferenceSuperLists.at(currentPageIndex)->rect();
    QRect lastEndPosition=currentPosition;
    QRect throwFromPosition=currentPosition;
    backupPage=currentPageIndex;
    if(pageIndex > currentPageIndex)
    {
        //This page is under the current page, move up
        throwFromPosition.setTop(lastEndPosition.height());
        lastEndPosition.setTop(-lastEndPosition.height());
    }
    else
    {
        //This page is above the current page, move down
        throwFromPosition.setTop(-lastEndPosition.height());
        lastEndPosition.setTop(lastEndPosition.height());
    }
    throwLastPage->setStartValue(currentPosition);
    throwLastPage->setEndValue(lastEndPosition);
    putCurrentPage->setStartValue(throwFromPosition);
    putCurrentPage->setEndValue(currentPosition);
    preferenceSuperLists.at(pageIndex)->setGeometry(throwFromPosition);
    moveAnimationGroup->addAnimation(throwLastPage);
    moveAnimationGroup->addAnimation(putCurrentPage);
    connect(moveAnimationGroup, SIGNAL(finished()),
            this, SLOT(hideBackupPage()));
    setPageVisible(pageIndex, true);
    moveAnimationGroup->start(QAbstractAnimation::DeleteWhenStopped);
    currentPageIndex=pageIndex;
}

void KCPreferencePager::hideBackupPage()
{
    setPageVisible(backupPage, false);
}

void KCPreferencePager::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    for(int i=0; i<preferenceSuperLists.count(); i++)
    {
        preferenceSuperLists.at(i)->resize(event->size());
    }
}
