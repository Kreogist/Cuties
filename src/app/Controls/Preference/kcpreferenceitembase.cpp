#include <QDebug>

#include "kcpreferenceitembase.h"

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
    originalValueDisplayer=new QLabel(this);
    setOriginalDisplayVisible(false);

    pal=originalValueDisplayer->palette();
    pal.setColor(QPalette::WindowText, QColor(150,150,150));
    originalValueDisplayer->setPalette(pal);

    //Set default switch
    valueChanged=false;
    editMode=false;

    //Set palette
    valueChangedAlpha=100;
    pal=palette();
    backgroundColor=QColor(0xf7,0xcf,0x3d,0);
    setBackgroundAlpha(0);

    //Init animation
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
    setCurrentValue(getUserNewValue());
    refreshValueDisplay();
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

void KCPreferenceItemBase::setOriginalDisplayVisible(bool statue)
{
    originalValueDisplayer->setEnabled(statue);
    originalValueDisplayer->setVisible(statue);
}


