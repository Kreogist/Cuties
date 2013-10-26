#include "kcsettinglistitemboolean.h"

KCSettingListItemBooleanSwitcher::KCSettingListItemBooleanSwitcher(QWidget *parent) :
    QLabel(parent)
{
    //Cache Image Control.
    switcherPixmapTrue=new QPixmap(":/Controls/image/Controls/BooleanTrue.png");
    switcherPixmapFalse=new QPixmap(":/Controls/image/Controls/BooleanFalse.png");
    //Set Default Value.
    setValue(false);
}

void KCSettingListItemBooleanSwitcher::setTheValue(bool NewValue)
{
    switcherValue=NewValue;
    setImage(switcherValue);
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
        setPixmap(*switcherPixmapTrue);
    }
    else
    {
        setPixmap(*switcherPixmapFalse);
    }
}

bool KCSettingListItemBooleanSwitcher::getValue()
{
    return switcherValue;
}

KCSettingListItemBoolean::KCSettingListItemBoolean(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    //This bool is used to fixed double anime when user changed value.
    animeChangedBugFixed=false;

    //Set Layout.
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set Layout.
    mainLayout->addSpacing(3);
    //Set Anime.
    ChangedAnime=new QTimeLine(500);
    connect(ChangedAnime,SIGNAL(frameChanged(int)),
            this,SLOT(setValueChangedAlpha(int)));
    //Set Palette.
    pal=this->palette();

    //Set Value Setter.
    valueSetter=new KCSettingListItemBooleanSwitcher(this);
    valueSetter->setEnabled(false);
    valueSetter->hide();
    mainLayout->addWidget(valueSetter);
    connect(valueSetter,SIGNAL(valueChanged()),this,SLOT(valueChangedAnimeEvent()));
    mainLayout->addSpacing(2);
    //Set Widget.
    mainLayout->addWidget(captionText);

    mainLayout->addStretch();

    setEditMode(false);
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
    if(valueSetter->getValue())
    {
        captionText->setText(enabledText);
    }
    else
    {
        captionText->setText(disabledText);
    }
}

void KCSettingListItemBoolean::setEnabledText(const QString &Text)
{
    enabledText=Text;
    refreshCaption();
}

QString KCSettingListItemBoolean::getEnabledText()
{
    return enabledText;
}

void KCSettingListItemBoolean::setDisabledText(const QString &Text)
{
    disabledText=Text;
    refreshCaption();
}

QString KCSettingListItemBoolean::getDisabledText()
{
    return disabledText;
}

bool KCSettingListItemBoolean::getValue()
{
    return valueSetter->getValue();
}

void KCSettingListItemBoolean::valueChangedAnimeEvent()
{
    ChangedAnime->stop();
    refreshCaption();
    if(valueSetter->getValue())
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
    if(!getEditMode())
    {
        KCSettingListItemBase::mousePressEvent(e);
        //Set Edit Mode Switcher.
        setEditMode(true);
    }
    setValue(!getValue());
    QWidget::mousePressEvent(e);
}

void KCSettingListItemBoolean::enterEvent(QEvent *e)
{
    if(!getEditMode())
    {
        valueSetter->setEnabled(true);
        valueSetter->show();
    }
    if(valueSetter->getValue())
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
    if(!getEditMode())
    {
        //Set Value Setter
        valueSetter->setEnabled(false);
        valueSetter->hide();
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
    valueSetter->setValue(NewValue);
}

void KCSettingListItemBoolean::setTheValue(bool NewValue)
{
    valueSetter->setTheValue(NewValue);
    refreshCaption();
}
