#include <QDebug>

#include "kcpreferenceitemboolean.h"

KCPreferenceItemBoolean::KCPreferenceItemBoolean(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    retranslate();

    enabledColor=QColor(0x54,0x8f,0x40);
    disabledColor=QColor(254, 0, 0);

    //Set Edit Mode Layout
    editLayout=new QVBoxLayout(this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);
    setLayout(editLayout);

    booleanLayout=new QHBoxLayout();
    booleanLayout->setContentsMargins(0,0,0,0);
    booleanLayout->setSpacing(0);

    booleanCaption=new QLabel(this);
    booleanLayout->addWidget(booleanCaption);
    booleanLayout->addSpacing(2);
    booleanLayout->addWidget(valueDisplayer);
    booleanLayout->addWidget(originalValueDisplayer);
    booleanLayout->addStretch();

    displayPalette=valueDisplayer->palette();

    editLayout->addLayout(booleanLayout);

    booleanData=new QCheckBox(this);
    booleanData->setText(booleanDataText);
    setEditWidgetStatus(false);
    editLayout->addWidget(booleanData);
    editLayout->addStretch();

    setExpandFinishedHeight(52);
}

KCPreferenceItemBoolean::~KCPreferenceItemBoolean()
{
    booleanLayout->deleteLater();
}

void KCPreferenceItemBoolean::setOriginalValue(const QVariant &value)
{
    booleanData->setChecked(value.toBool());
    KCPreferenceItemBase::setOriginalValue(value);
    valueDisplayer->setText(booleanStatusText[int(value.toBool())]);
    displayPalette.setColor(QPalette::WindowText, value.toBool()?enabledColor:disabledColor);
    valueDisplayer->setPalette(displayPalette);

    /*
     * Change logical:
     *
     * When we set a original value, we connent the signal and slot this time.
     */
    connect(booleanData, SIGNAL(stateChanged(int)),
            this, SLOT(valueChangedEvent()));
}

QString KCPreferenceItemBoolean::getBooleanText() const
{
    return booleanText;
}

void KCPreferenceItemBoolean::setBooleanText(const QString &value)
{
    booleanText = value;
}

void KCPreferenceItemBoolean::setBooleanCaptionText(const QString &value)
{
    booleanCaption->setText(value);
}

void KCPreferenceItemBoolean::retranslate()
{
    booleanDataText=tr("Enabled this feature.");
    booleanStatusText[1]=tr("Enabled");
    booleanStatusText[0]=tr("Disable");
}

void KCPreferenceItemBoolean::retranslateAndSet()
{
    retranslate();
    booleanData->setText(booleanDataText);
}

void KCPreferenceItemBoolean::setEditWidgetStatus(bool states)
{
    booleanData->setVisible(states);
    booleanData->setEnabled(states);
}

void KCPreferenceItemBoolean::setWidgetValue(QVariant newWidgeValue)
{
    booleanData->setChecked(newWidgeValue.toBool());
}

QVariant KCPreferenceItemBoolean::getUserNewValue()
{
    return booleanData->isChecked();
}

void KCPreferenceItemBoolean::refreshValueDisplay()
{
    valueDisplayer->setText(booleanStatusText[int(booleanData->isChecked())]);
    displayPalette.setColor(QPalette::WindowText, booleanData->isChecked()?enabledColor:disabledColor);
    valueDisplayer->setPalette(displayPalette);
    if(booleanData->isChecked() == originalValue.toBool())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(" (" +
                                    originalValueIs +
                                    booleanStatusText[int(originalValue.toBool())] +
                                    ")");
    setOriginalDisplayVisible(true);
}

void KCPreferenceItemBoolean::refreshBooleanText()
{
    booleanData->setText(booleanText);
}
