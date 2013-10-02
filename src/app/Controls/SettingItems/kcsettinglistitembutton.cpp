#include "kcsettinglistitembutton.h"

KCSettingListItemButton::KCSettingListItemButton(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setFixedHeight(27);

    //Set Palette.
    pal=this->palette();
    pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,0));
    setPalette(pal);

    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    Caption=new QLabel(this);
    mainLayout->addWidget(Caption,0,Qt::AlignCenter);
}

void KCSettingListItemButton::setButtonText(QString newButtonText)
{
    Caption->setText(newButtonText);
}

void KCSettingListItemButton::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    //Set New Background.
    pal.setColor(QPalette::Window,QColor(0xf7,0xcf,0x3d,100));
    setPalette(pal);
}

void KCSettingListItemButton::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    //Set New Background.
    pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,0));
    setPalette(pal);
}

void KCSettingListItemButton::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    //Set New Background.
    pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,255));
    setPalette(pal);
    emit buttonPressed();
}

void KCSettingListItemButton::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    //Set New Background.
    pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,100));
    setPalette(pal);
}
