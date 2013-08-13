#include "kciscrollarea.h"

kciScrollArea::kciScrollArea(QWidget *parent) :
    QWidget(parent)
{
    horizontalScrollBar=new QScrollBar(this);
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    verticalScrollBar=new QScrollBar(this);
    verticalScrollBar->setOrientation(Qt::Vertical);
}

void kciScrollArea::setWidget(QWidget *widget)
{
    widget->setParent(this);
    widget->setGeometry(0,
                        0,
                        widget->width(),
                        widget->height());
}
