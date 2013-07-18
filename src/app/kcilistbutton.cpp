#include "kcilistbutton.h"

kciListButton::kciListButton(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    //Set QPalette.
    pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(pal);

    //Init Label.
    lblButtonText=new QLabel(this);
    lblButtonIcon=new QLabel(this);
    //Init and set Layout.
    mLayout=new QHBoxLayout(this);
    mLayout->setContentsMargins(5,5,5,5);
    setLayout(mLayout);
    //Add Widget.
    //mLayout->addSpacing(5);
    mLayout->addWidget(lblButtonIcon);
    mLayout->addWidget(lblButtonText);
    mLayout->addStretch();
}

void kciListButton::setLabelIcon(const QString &fileName)
{
    lblButtonIcon->setPixmap(QPixmap(fileName));
}

void kciListButton::setLabelText(const QString &text)
{
    lblButtonText->setText(text);
}

void kciListButton::enterEvent(QEvent *event)
{
    pal.setColor(QPalette::Window, QColor(255,255,255,255));
    this->setPalette(pal);
    QWidget::enterEvent(event);
}

void kciListButton::leaveEvent(QEvent *event)
{
    pal.setColor(QPalette::Window, QColor(0,0,0,0));
    this->setPalette(pal);
    QWidget::leaveEvent(event);
}
