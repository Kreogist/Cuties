#include "kcisettinglistitemboolean.h"

kciSettingListItemBooleanSwitcher::kciSettingListItemBooleanSwitcher(QWidget *parent) :
    QLabel(parent)
{
    //Cache Image Control.
    pxpTrue=new QPixmap(":/Controls/image/Controls/BooleanTrue.png");
    pxpFalse=new QPixmap(":/Controls/image/Controls/BooleanFalse.png");
    //Set Default Value.
    setValue(false);
}

void kciSettingListItemBooleanSwitcher::setValue(bool NewValue)
{
    Value=NewValue;
    setImage(Value);
}

void kciSettingListItemBooleanSwitcher::setImage(bool NewValue)
{
    if(NewValue)
    {
        setPixmap(*pxpTrue);
    }
    else
    {
        setPixmap(*pxpFalse);
    }
    emit valueChanged();
}

bool kciSettingListItemBooleanSwitcher::getValue()
{
    return Value;
}

kciSettingListItemBoolean::kciSettingListItemBoolean(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    //This bool is used to fixed double anime when user changed value.
    animeChangedBugFixed=false;

    //Set Layout.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Set Layout.
    MainLayout->addSpacing(1);
    //Set Anime.
    ChangedAnime=new QTimeLine(500);
    connect(ChangedAnime,SIGNAL(frameChanged(int)),
            this,SLOT(setValueChangedAlpha(int)));
    //Set Palette.
    pal=this->palette();

    //Set Value Setter.
    ValueSetter=new kciSettingListItemBooleanSwitcher(this);
    ValueSetter->setEnabled(false);
    ValueSetter->hide();
    MainLayout->addWidget(ValueSetter);
    connect(ValueSetter,SIGNAL(valueChanged()),this,SLOT(valueChangedAnimeEvent()));
    MainLayout->addSpacing(4);
    //Set Widget.
    MainLayout->addWidget(Caption);

    MainLayout->addStretch();

    blnEditMode=false;
}

void kciSettingListItemBoolean::valueChangedEvent()
{
    refreshCaption();
}

void kciSettingListItemBoolean::refreshCaption()
{
    if(ValueSetter->getValue())
    {
        Caption->setText(strEnabledInfo);
    }
    else
    {
        Caption->setText(strDisabledInfo);
    }
}

void kciSettingListItemBoolean::setEnabledText(const QString &Text)
{
    strEnabledInfo=Text;
    refreshCaption();
}

QString kciSettingListItemBoolean::getEnabledText()
{
    return strEnabledInfo;
}

void kciSettingListItemBoolean::setDisabledText(const QString &Text)
{
    strDisabledInfo=Text;
    refreshCaption();
}

QString kciSettingListItemBoolean::getDisabledText()
{
    return strDisabledInfo;
}

bool kciSettingListItemBoolean::getItemValue()
{
    return ValueSetter->getValue();
}

void kciSettingListItemBoolean::valueChangedAnimeEvent()
{
    ChangedAnime->stop();
    refreshCaption();
    if(ValueSetter->getValue())
    {
        pal.setColor(QPalette::Window, QColor(123,170,43,255));
        setPalette(pal);
    }
    else
    {
        pal.setColor(QPalette::Window, QColor(222,2,28,255));
        setPalette(pal);
    }
    ChangedAnime->setFrameRange(255,0);
    ChangedAnime->start();
    animeChangedBugFixed=true;
}

void kciSettingListItemBoolean::setValueChangedAlpha(int alpha)
{
    QColor windowColor=pal.color(QPalette::Window);
    windowColor.setAlpha(alpha);
    pal.setColor(QPalette::Window,windowColor);
    setPalette(pal);
}

void kciSettingListItemBoolean::mousePressEvent(QMouseEvent *e)
{
    if(!blnEditMode)
    {
        kciSettingListItemBase::mousePressEvent(e);
        //Set Edit Mode
        ValueSetter->setEnabled(true);
        ValueSetter->show();
        //Set Edit Mode Switcher.
        blnEditMode=true;
    }
    else
    {
        setItemValue(!getItemValue());
    }
    e->accept();
}

void kciSettingListItemBoolean::leaveEvent(QEvent *e)
{
    if(!blnEditMode || (blnEditMode && ChangedAnime->state()==QTimeLine::NotRunning))
    {
        if(!animeChangedBugFixed)
        {
            kciSettingListItemBase::leaveEvent(e);
        }
        else
        {
            animeChangedBugFixed=false;
        }
    }
}

void kciSettingListItemBoolean::setItemValue(bool NewValue)
{
    ValueSetter->setValue(NewValue);
}

void kciSettingListItemBoolean::enterEvent(QEvent *e)
{
    if(!blnEditMode || (blnEditMode && ChangedAnime->state()==QTimeLine::NotRunning))
    {
        if(!animeChangedBugFixed)
        {
            kciSettingListItemBase::enterEvent(e);
        }
        else
        {
            animeChangedBugFixed=false;
        }
    }
}
