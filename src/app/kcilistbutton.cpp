#include "kcilistbutton.h"

kciListButton::kciListButton(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    //Set Background Color.
    bgColor=new QColor();
    bgColor->setRgb(0,0,0,0);
    //Set Pushed Color.
    pushed=false;++
    pushedColor=new QColor();
    pushedColor->setRgb(0,0,0,100);
    //Set Text Color.
    textColor=new QColor();
    textColor->setRgb(0,0,0,255);
    //Set Pushed Text Color.
    pushedTextColor=new QColor();
    pushedTextColor->setRgb(255,255,255,255);
    //Set QPalette.
    pal=palette();
    pal.setColor(QPalette::Window, *bgColor);
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
    if(!pushed)
    {
        pal.setColor(QPalette::Window, QColor(255,255,255,255));
        this->setPalette(pal);
    }
    QWidget::enterEvent(event);
}

void kciListButton::leaveEvent(QEvent *event)
{
    if(!pushed)
    {
        pal.setColor(QPalette::Window, *bgColor);
        this->setPalette(pal);
    }
    QWidget::leaveEvent(event);
}

void kciListButton::mousePressEvent(QMouseEvent *e)
{
    if(!pushed)
    {
        if(e->buttons() == Qt::LeftButton)
        {
            emit click();
        }
    }
    QWidget::mousePressEvent(e);
}

void kciListButton::setBackgroundColor(const QColor &NewColor)
{
    *bgColor=NewColor;
    pal.setColor(QPalette::Window, *bgColor);
    this->setPalette(pal);
}

QColor kciListButton::getBackgroundColor()
{
    return *bgColor;
}

void kciListButton::setPushed(bool newValue)
{
    pushed=newValue;
    if(pushed)
    {
        pal.setColor(QPalette::Window, *pushedColor);
        pal.setColor(QPalette::WindowText, *pushedTextColor);
        this->setPalette(pal);
    }
    else
    {
        setBackgroundColor(*bgColor);
        setTextColor(*textColor);
    }
}

bool kciListButton::getPushed()
{
    return pushed;
}

void kciListButton::setTextColor(const QColor &NewColor)
{
    *textColor=NewColor;
    pal.setColor(QPalette::WindowText, *textColor);
    this->setPalette(pal);
}

QColor kciListButton::getTextColor()
{
    return *textColor;
}

void kciListButton::setPushedTextColor(const QColor &NewColor)
{
    *pushedTextColor=NewColor;
}

QColor kciListButton::getPushedTextColor()
{
    return *pushedTextColor;
}
