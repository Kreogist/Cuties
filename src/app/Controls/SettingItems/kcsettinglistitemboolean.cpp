#include "kcsettinglistitemboolean.h"

KCSettingListItemBooleanSwitcher::KCSettingListItemBooleanSwitcher(QWidget *parent) :
    QLabel(parent)
{
    //Cache Image Control.
    pxpTrue=new QPixmap(":/Controls/image/Controls/BooleanTrue.png");
    pxpFalse=new QPixmap(":/Controls/image/Controls/BooleanFalse.png");
    //Set Default Value.
    setValue(false);
}

void KCSettingListItemBooleanSwitcher::setTheValue(bool NewValue)
{
    Value=NewValue;
    setImage(Value);
}

void KCSettingListItemBooleanSwitcher::setValue(bool NewValue)
{
    setTheValue(NewValue);
    emit valueChanged();
}

void KCSettingListItemBooleanSwitcher::setImage(bool NewValue)
{
    if(NewValue)
    {
        setPixmap(*pxpTrue);
    }
    else
    {
        setPixmap(*pxpFalse);
    }
}

bool KCSettingListItemBooleanSwitcher::getValue()
{
    return Value;
}

KCSettingListItemBoolean::KCSettingListItemBoolean(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    //This bool is used to fixed double anime when user changed value.
    animeChangedBugFixed=false;

    //Set Layout.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Set Layout.
    MainLayout->addSpacing(3);
    //Set Anime.
    ChangedAnime=new QTimeLine(500);
    connect(ChangedAnime,SIGNAL(frameChanged(int)),
            this,SLOT(setValueChangedAlpha(int)));
    //Set Palette.
    pal=this->palette();

    //Set Value Setter.
    ValueSetter=new KCSettingListItemBooleanSwitcher(this);
    ValueSetter->setEnabled(false);
    ValueSetter->hide();
    MainLayout->addWidget(ValueSetter);
    connect(ValueSetter,SIGNAL(valueChanged()),this,SLOT(valueChangedAnimeEvent()));
    MainLayout->addSpacing(2);
    //Set Widget.
    MainLayout->addWidget(Caption);

    MainLayout->addStretch();

    blnEditMode=false;
    animeMouseLeaveFadeOut=new QTimeLine(200, this);
    connect(animeMouseLeaveFadeOut, SIGNAL(frameChanged(int)),
            this, SLOT(setValueChangedAlpha(int)));
}

void KCSettingListItemBoolean::valueChangedEvent()
{
    refreshCaption();
}

void KCSettingListItemBoolean::refreshCaption()
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

void KCSettingListItemBoolean::setEnabledText(const QString &Text)
{
    strEnabledInfo=Text;
    refreshCaption();
}

QString KCSettingListItemBoolean::getEnabledText()
{
    return strEnabledInfo;
}

void KCSettingListItemBoolean::setDisabledText(const QString &Text)
{
    strDisabledInfo=Text;
    refreshCaption();
}

QString KCSettingListItemBoolean::getDisabledText()
{
    return strDisabledInfo;
}

bool KCSettingListItemBoolean::getValue()
{
    return ValueSetter->getValue();
}

void KCSettingListItemBoolean::valueChangedAnimeEvent()
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
    ChangedAnime->setFrameRange(255,100);
    ChangedAnime->start();
    animeChangedBugFixed=true;
}

void KCSettingListItemBoolean::setValueChangedAlpha(int alpha)
{
    QColor windowColor=pal.color(QPalette::Window);
    windowColor.setAlpha(alpha);
    pal.setColor(QPalette::Window,windowColor);
    setPalette(pal);
}

void KCSettingListItemBoolean::mousePressEvent(QMouseEvent *e)
{
    if(!blnEditMode)
    {
        KCSettingListItemBase::mousePressEvent(e);
        //Set Edit Mode Switcher.
        blnEditMode=true;
    }
    setValue(!getValue());
    e->accept();
    QWidget::mousePressEvent(e);
}

void KCSettingListItemBoolean::enterEvent(QEvent *e)
{
    if(!blnEditMode)
    {
        ValueSetter->setEnabled(true);
        ValueSetter->show();
    }
    if(ValueSetter->getValue())
    {
        if(animeMouseLeaveFadeOut->state()==QTimeLine::NotRunning)
        {
            pal.setColor(QPalette::Window, QColor(123,170,43,100));
            setPalette(pal);
        }
    }
    else
    {
        if(animeMouseLeaveFadeOut->state()==QTimeLine::NotRunning)
        {
            pal.setColor(QPalette::Window, QColor(222,2,28,100));
            setPalette(pal);
        }
    }
    QWidget::enterEvent(e);
}

void KCSettingListItemBoolean::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    if(!blnEditMode)
    {
        //Set Value Setter
        ValueSetter->setEnabled(false);
        ValueSetter->hide();
    }
    if(ChangedAnime->state()==QTimeLine::NotRunning)
    {
        //Stop Leave Animation.
        animeMouseLeaveFadeOut->stop();
        //Set Leave Animation.
        animeMouseLeaveFadeOut->setStartFrame(100);
        animeMouseLeaveFadeOut->setEndFrame(0);
        animeMouseLeaveFadeOut->start();
    }
    else
    {
        ChangedAnime->stop();
        //Set Leave Animation.
        animeMouseLeaveFadeOut->setStartFrame(this->palette().window().color().alpha());
        animeMouseLeaveFadeOut->setEndFrame(0);
        animeMouseLeaveFadeOut->start();
    }
}

void KCSettingListItemBoolean::setValue(bool NewValue)
{
    ValueSetter->setValue(NewValue);
}

void KCSettingListItemBoolean::setTheValue(bool NewValue)
{
    ValueSetter->setTheValue(NewValue);
    refreshCaption();
}
