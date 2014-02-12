
#include <QDebug>

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

#include "kccolorselector.h"

#include "kcpreferenceitemcolor.h"

KCPreferenceColorViewer::KCPreferenceColorViewer(QWidget *parent) :
    QLabel(parent)
{
    setAutoFillBackground(true);
    pal=palette();
}

void KCPreferenceColorViewer::setColor(const QColor &value)
{
    pal.setColor(QPalette::Window, value);
    setPalette(pal);
}

void KCPreferenceColorViewer::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    pointer=event->pos();
}

void KCPreferenceColorViewer::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    if(rect().contains(pointer))
    {
        emit viewerClicked();
    }
}

KCPreferenceColorLabel::KCPreferenceColorLabel(QWidget *parent) :
    QWidget(parent)
{
    retranslate();

    setContentsMargins(0,0,0,0);

    colorLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    colorLayout->setContentsMargins(0,0,0,0);
    colorLayout->setSpacing(4);
    setLayout(colorLayout);

    viewer=new KCPreferenceColorViewer(this);
    colorLayout->addWidget(viewer,1);
    selectColor=new QPushButton(selectColorCaption, this);
    colorLayout->addWidget(selectColor);

    connect(viewer, SIGNAL(viewerClicked()),
            this, SLOT(onActionBrowseColor()));
    connect(selectColor, SIGNAL(clicked()),
            this, SLOT(onActionBrowseColor()));
}

QColor KCPreferenceColorLabel::getCurrentColor() const
{
    return currentColor;
}

void KCPreferenceColorLabel::setCurrentColor(const QColor &value)
{
    currentColor = value;
    viewer->setColor(value);
}

void KCPreferenceColorLabel::retranslate()
{
    selectColorCaption=tr("Select Color");
}

void KCPreferenceColorLabel::retranslateAndSet()
{
    retranslate();
    selectColor->setText(selectColorCaption);
}

void KCPreferenceColorLabel::onActionBrowseColor()
{
    KCColorSelector *selector=new KCColorSelector(this);
    selector->setOriginalColor(currentColor);
    selector->exec();
    QColor testColor=selector->getCurrentColor();
    if(testColor==currentColor)
    {
        return;
    }
    setCurrentColor(testColor);
    emit colorChanged(currentColor);
}

KCPreferenceItemColor::KCPreferenceItemColor(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    //Set Edit Mode Layout
    editLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);
    setLayout(editLayout);

    colorLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    colorLayout->setContentsMargins(0,0,0,0);
    colorLayout->setSpacing(0);

    colorCaption=new QLabel(this);
    colorLayout->addWidget(colorCaption);
    colorLayout->addSpacing(2);
    colorLayout->addWidget(valueDisplayer);
    colorLayout->addWidget(originalValueDisplayer);
    colorLayout->addStretch();

    editLayout->addLayout(colorLayout);

    colorData=new KCPreferenceColorLabel(this);
    setEditWidgetStatus(false);
    editLayout->addWidget(colorData);
    editLayout->addStretch();

    setExpandFinishedHeight(50);
}

KCPreferenceItemColor::~KCPreferenceItemColor()
{
    colorLayout->deleteLater();
}

void KCPreferenceItemColor::setOriginalValue(const QVariant &value)
{
    QColor originalColor=value.value<QColor>();
    colorData->setCurrentColor(originalColor);
    valueDisplayer->setText(getColorString(originalColor));
    KCPreferenceItemBase::setOriginalValue(value);

    connect(colorData, SIGNAL(colorChanged(QColor)),
            this, SLOT(valueChangedEvent()));
}

void KCPreferenceItemColor::setColorCaptionText(const QString &value)
{
    colorCaption->setText(value);
}

void KCPreferenceItemColor::retranslateAndSet()
{
    colorData->retranslateAndSet();
}

QVariant KCPreferenceItemColor::getUserNewValue()
{
    return colorData->getCurrentColor();
}

void KCPreferenceItemColor::refreshValueDisplay()
{
    valueDisplayer->setText(getColorString(colorData->getCurrentColor()));
    if(colorData->getCurrentColor() == originalValue.value<QColor>())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(QString(" (" +
                                            originalValueIs +
                                            getColorString(originalValue.value<QColor>()) +
                                            ")"));
    setOriginalDisplayVisible(true);
}

void KCPreferenceItemColor::setEditWidgetStatus(bool states)
{
    colorData->setVisible(states);
    colorData->setEnabled(states);
}

void KCPreferenceItemColor::setWidgetValue(QVariant newWidgeValue)
{
    colorData->setCurrentColor(newWidgeValue.value<QColor>());
}

QString KCPreferenceItemColor::getColorString(const QColor &value) const
{
    return QString("#"+
                   QString::number(value.red(), 16)+
                   QString::number(value.green(), 16)+
                   QString::number(value.blue(), 16));
}
