#include "kcsettinglistitembase.h"

KCSettingListItemBase::KCSettingListItemBase(QWidget *parent) :
    QWidget(parent)
{
    //Set Auto Fill Background.
    setAutoFillBackground(true);
    //Set Default Height.
    setFixedHeight(27);
    //Set Palette.
    pal=this->palette();
    pal.setColor(QPalette::Window, QColor(0xf7,0xcf,0x3d,0));
    setPalette(pal);
    //Set Label.
    captionText=new QLabel(this);

    //Set Selected Status.
    itemSelected=false;
    editMode=false;

    //Set Fade Out Anime.
    animationBackgroundFadeOut=new QTimeLine(200,this);
    connect(animationBackgroundFadeOut,SIGNAL(frameChanged(int)),
            this,SLOT(changeBackgroundAlpha(int)));
}

bool KCSettingListItemBase::getEditMode()
{
    return editMode;
}

bool KCSettingListItemBase::getItemSelectedStatus()
{
    return itemSelected;
}

void KCSettingListItemBase::enterEvent(QEvent *e)
{
    if(!itemSelected)
    {
        //Stop Anime AnyWay.
        animationBackgroundFadeOut->stop();
        //Set New Background.
        pal.setColor(QPalette::Window,QColor(0xf7,0xcf,0x3d,200));
        setPalette(pal);
    }
    QWidget::enterEvent(e);
}

void KCSettingListItemBase::leaveEvent(QEvent *e)
{
    if(!itemSelected)
    {
        int nowAlpha=pal.color(QPalette::Window).alpha();
        animationBackgroundFadeOut->stop();
        animationBackgroundFadeOut->setFrameRange(nowAlpha,0);
        animationBackgroundFadeOut->start();
    }
    QWidget::leaveEvent(e);
}

void KCSettingListItemBase::changeBackgroundAlpha(int alpha)
{
    pal.setColor(QPalette::Window,QColor(0xf7,0xcf,0x3d,alpha));
    setPalette(pal);
}

void KCSettingListItemBase::mousePressEvent(QMouseEvent *e)
{
    changeBackgroundAlpha(255);
    QWidget::mousePressEvent(e);
    emit itemGetFocus();
}

void KCSettingListItemBase::setEditMode(bool value)
{
    editMode=value;
}

void KCSettingListItemBase::setItemSelected(bool value)
{
    itemSelected=value;
}
