#include "kciscrollarea.h"

kciScrollArea::kciScrollArea(QWidget *parent) :
    QWidget(parent)
{
    horizontalScrollBar=new QScrollBar(this);
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    verticalScrollBar=new QScrollBar(this);
    verticalScrollBar->setOrientation(Qt::Vertical);
    verticalScrollBar->setVisible(false);
    verticalScrollBar->setEnabled(false);
}

void kciScrollArea::setWidget(QWidget *widget)
{
    widget->setParent(this);
    widget->setGeometry(0,
                        0,
                        widget->width(),
                        widget->height());
    //HSB Should be shown?
    if(widget->minimumWidth() > width())
    {
        verticalScrollBar->setVisible(true);
        verticalScrollBar->setEnabled(true);
    }
    else
    {
        widget->setFixedWidth(width());
        verticalScrollBar->setVisible(false);
        verticalScrollBar->setEnabled(false);
    }
}
