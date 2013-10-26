#include "kclistbutton.h"

KCListButton::KCListButton(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    //Set Background Color.
    bgColor=new QColor();
    bgColor->setRgb(0,0,0,0);
    //Set Pushed Color.
    pushed=false;
    pushedColor=new QColor();
    pushedColor->setRgb(255,255,255);
    //Set Text Color.
    textColor=new QColor();
    textColor->setRgb(0,0,0,255);
    //Set Pushed Text Color.
    pushedTextColor=new QColor();
    pushedTextColor->setRgb(0,0,0,255);
    //Set Hover Color.
    hoverColor=new QColor();
    hoverColor->setRgb(0xf7,0xcf,0x3d,255);
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

void KCListButton::setLabelIcon(const QString &fileName)
{
    lblButtonIcon->setPixmap(QPixmap(fileName));
}

void KCListButton::setLabelText(const QString &text)
{
    lblButtonText->setText(text);
}

void KCListButton::enterEvent(QEvent *event)
{
    if(!pushed)
    {
        pal.setColor(QPalette::Window, *hoverColor);
        this->setPalette(pal);
    }
    QWidget::enterEvent(event);
}

void KCListButton::leaveEvent(QEvent *event)
{
    if(!pushed)
    {
        pal.setColor(QPalette::Window, *bgColor);
        this->setPalette(pal);
    }
    QWidget::leaveEvent(event);
}

void KCListButton::mousePressEvent(QMouseEvent *e)
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

void KCListButton::setBackgroundColor(const QColor &NewColor)
{
    *bgColor=NewColor;
    pal.setColor(QPalette::Window, *bgColor);
    this->setPalette(pal);
}

QColor KCListButton::getBackgroundColor()
{
    return *bgColor;
}

void KCListButton::setPushed(bool newValue)
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

bool KCListButton::getPushed()
{
    return pushed;
}

void KCListButton::setTextColor(const QColor &NewColor)
{
    *textColor=NewColor;
    pal.setColor(QPalette::WindowText, *textColor);
    this->setPalette(pal);
}

QColor KCListButton::getTextColor()
{
    return *textColor;
}

void KCListButton::setPushedTextColor(const QColor &NewColor)
{
    *pushedTextColor=NewColor;
}

QColor KCListButton::getPushedTextColor()
{
    return *pushedTextColor;
}

void KCListButton::setHoverColor(const QColor &NewColor)
{
    *hoverColor=NewColor;
}

QColor KCListButton::getHoverColor()
{
    return *hoverColor;
}

QWidget *KCListButton::getUserInterfaceWidget() const
{
    return UserInterfaceWidget;
}

void KCListButton::setUserInterfaceWidget(QWidget *value)
{
    UserInterfaceWidget = value;
}
