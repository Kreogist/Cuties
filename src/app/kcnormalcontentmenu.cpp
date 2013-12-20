
#include <QDebug>
#include <QStyleFactory>
#include <QCursor>

#include "kcnormalcontentmenu.h"

KCNormalContentMenu::KCNormalContentMenu(QWidget *parent) :
    QMenu(parent)
{
    setStyle(QStyleFactory::create("fustion"));
    showAnimation=new QPropertyAnimation(this, "geometry", this);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void KCNormalContentMenu::showEvent(QShowEvent *e)
{
    QPoint coursePoint=QCursor::pos();
    QRect endPosition=geometry();
    QRect startPostion=endPosition;
    if(coursePoint.y()==startPostion.y())
    {
        //Expand from top
        startPostion.setHeight(0);
    }
    else
    {
        //Expand form bottom
        startPostion.setTop(startPostion.top()+startPostion.height());
        startPostion.setHeight(0);
    }
    showAnimation->setStartValue(startPostion);
    showAnimation->setEndValue(endPosition);
    showAnimation->start();
    QMenu::showEvent(e);
}
