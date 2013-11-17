#include <QDebug>

#include "kcpreferenceitembase.h"

KCPreferenceOriginalLabel::KCPreferenceOriginalLabel(QWidget *parent) :
    QLabel(parent)
{
    ;
}

void KCPreferenceOriginalLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    emit requireResetCurrentValue();
}

KCPreferenceItemBase::KCPreferenceItemBase(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(27);

    //Set Language
    retranslate();

    //Set the original value displayer.
    valueDisplayer=new QLabel(this);
    originalValueDisplayer=new KCPreferenceOriginalLabel(this);
    setOriginalDisplayVisible(false);

    pal=originalValueDisplayer->palette();
    pal.setColor(QPalette::WindowText, QColor(150,150,150));
    originalValueDisplayer->setPalette(pal);

    connect(originalValueDisplayer, SIGNAL(requireResetCurrentValue()),
            this, SLOT(resetCurrentValue()));

    //Set default switch
    valueChanged=false;
    editMode=false;

    //Set palette
    valueChangedAlpha=100;
    pal=palette();
    backgroundColor=QColor(0xf7,0xcf,0x3d,0);
    setBackgroundAlpha(0);

    //Init animation
    //Fade out Animation
    fadeMeOut=new QTimeLine(100, this);
    fadeMeOut->setStartFrame(255);
    connect(fadeMeOut, SIGNAL(frameChanged(int)),
            this, SLOT(setBackgroundAlpha(int)));

    //Expand Animation
    expandAnimation=new QTimeLine(100, this);
    expandAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(expandAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(setItemHeight(int)));
    connect(expandAnimation, SIGNAL(finished()),
            this, SLOT(showEditWidget()));

    //Fold Animation
    foldAnimation=new QTimeLine(100, this);
    foldAnimation->setEndFrame(27);
    foldAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(foldAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(setItemHeight(int)));

    //Show Animation
    showAnimation=new QTimeLine(100, this);
    showAnimation->setEndFrame(27);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(showAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(setItemHeight(int)));

    //Hide Animation
    hideAnimation=new QTimeLine(100, this);
    hideAnimation->setEndFrame(0);
    hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(setItemHeight(int)));
    connect(hideAnimation, SIGNAL(finished()),
            this, SLOT(hide()));
}

QVariant KCPreferenceItemBase::getCurrentValue() const
{
    return currentValue;
}

void KCPreferenceItemBase::setCurrentValue(const QVariant &value)
{
    currentValue=value;
    valueChanged=(currentValue!=originalValue);
}

QVariant KCPreferenceItemBase::getOriginalValue() const
{
    return originalValue;
}

void KCPreferenceItemBase::setOriginalValue(const QVariant &value)
{
    originalValue = value;
    currentValue = value;
}

void KCPreferenceItemBase::editFinished()
{
    expandAnimation->stop();
    if(valueChanged)
    {
        fadeMeOut->setEndFrame(valueChangedAlpha);
    }
    else
    {
        fadeMeOut->setEndFrame(0);
    }
    editMode=false;
    foldAnimation->setStartFrame(height());
    hideEditWidget();
    foldAnimation->start();
    fadeMeOut->start();
}

void KCPreferenceItemBase::setExpandFinishedHeight(const int &endHeight)
{
    expandEndHeight=endHeight;
    expandAnimation->setEndFrame(endHeight);
}

int KCPreferenceItemBase::getExpandFinishedHeight() const
{
    return expandEndHeight;
}

void KCPreferenceItemBase::retranslate()
{
    originalValueIs=tr("Original Setting: ");
}

void KCPreferenceItemBase::retranslateAndSet()
{
    retranslate();
    refreshValueDisplay();
}

void KCPreferenceItemBase::heightState(bool newState)
{
    if(newState)
    {
        setFixedHeight(27);
        show();
    }
    else
    {
        setFixedHeight(0);
        hide();
    }
}

void KCPreferenceItemBase::animateShow()
{
    if(showAnimation->state()!=QTimeLine::Running)
    {
        //Prepare animation
        show();
        //Stop hide animation
        hideAnimation->stop();
        //Set show animation
        showAnimation->setStartFrame(height());
        showAnimation->start();
    }
}

void KCPreferenceItemBase::animateHide()
{
    if(hideAnimation->state()!=QTimeLine::Running)
    {
        //Stop show animation
        showAnimation->stop();
        //Set hide animation
        hideAnimation->setStartFrame(height());
        hideAnimation->start();
    }
}

void KCPreferenceItemBase::resetCurrentValue()
{
    setWidgetValue(getOriginalValue());
}

void KCPreferenceItemBase::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    setBackgroundAlpha(255);
    if(!editMode)
    {
        foldAnimation->stop();
        expandAnimation->setStartFrame(height());
        expandAnimation->start();
        editMode=true;
    }
    emit editFocusCapture();
}

void KCPreferenceItemBase::setBackgroundAlpha(int newAlpha)
{
    backgroundColor.setAlpha(newAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

void KCPreferenceItemBase::setItemHeight(int newHeight)
{
    setFixedHeight(newHeight);
}

void KCPreferenceItemBase::showEditWidget()
{
    setEditWidgetStatus(true);
}

void KCPreferenceItemBase::hideEditWidget()
{
    setEditWidgetStatus(false);
}

void KCPreferenceItemBase::valueChangedEvent()
{
    setCurrentValue(getUserNewValue());
    refreshValueDisplay();
}

void KCPreferenceItemBase::setOriginalDisplayVisible(bool statue)
{
    originalValueDisplayer->setEnabled(statue);
    originalValueDisplayer->setVisible(statue);
}
